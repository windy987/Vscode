import requests
from bs4 import BeautifulSoup

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}
url = "https://www.baidu.com"
res = requests.get(url, headers=headers)
res.encoding = 'utf-8'

print(res.status_code)

soup = BeautifulSoup(res.text, 'lxml')

title = soup.title.string
print(title)

links = soup.find_all('a')
for x in links:
    l = x.get('href')
    print(l)