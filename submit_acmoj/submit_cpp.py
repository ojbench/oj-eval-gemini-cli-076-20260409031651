import os
import sys
import requests

def submit_cpp(problem_id, file_path):
    token = os.environ.get("ACMOJ_TOKEN")
    headers = {"Authorization": f"Bearer {token}"}
    with open(file_path, "r") as f:
        code = f.read()
    data = {"language": "cpp", "code": code}
    url = f"https://acm.sjtu.edu.cn/OnlineJudge/api/v1/problem/{problem_id}/submit"
    response = requests.post(url, headers=headers, data=data)
    print(response.json())

if __name__ == "__main__":
    submit_cpp(1363, "MyList.hpp")
