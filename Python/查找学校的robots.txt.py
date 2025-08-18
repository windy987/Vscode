import requests

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}
url = 'https://www.nuist.edu.cn/robots.txt'
res = requests.get(url, headers = headers)
print(res.status_code)