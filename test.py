import requests
from bs4 import BeautifulSoup

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}

url = "https://bulletin.nuist.edu.cn/wjgg.htm"
res = requests.get(url, headers=headers)
res.encoding = 'utf-8'

soup = BeautifulSoup(res.text, 'lxml')

btt = soup.find_all("span", class_="btt" )
print(btt)
