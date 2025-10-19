练习用
为git添加过代理设置
git config --global http.proxy  http://127.0.0.1:7892
git config --global https.proxy http://127.0.0.1:7892
回滚设置
git config --global --unset http.proxy
git config --global --unset https.proxy