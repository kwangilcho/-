import requests
from bs4 import BeautifulSoup
import sys

def has_argument():
    return len(sys.argv) > 1
    
if __name__ == '__main__':
    if not has_argument():
        quit()

    base_url = 'https://algospot.com/judge/problem/read/'
    problem_name = sys.argv[1].upper()

    response = requests.get(base_url + problem_name)
    if response.status_code != 200:
        print("문제 요청을 실패하였습니다.")
        quit()
    
    bs = BeautifulSoup(response.text, 'html.parser')
    sample_input = bs.find('section', class_='problem_sample_input').pre.get_text()
    sample_output = bs.find('section', class_='problem_sample_output').pre.get_text()

    with open(problem_name + '_input', 'w') as f:
        f.write(sample_input)
        print(problem_name, "테스트 입력을 생성하였습니다.")

    with open(problem_name + '_output', 'w') as f:
        f.write(sample_output)
        print(problem_name, "테스트 정답을 생성하였습니다.")
