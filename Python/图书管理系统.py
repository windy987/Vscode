'''
## 📘 综合练习题：图书馆图书借阅系统（简易版）

请你编写一个控制台程序，模拟图书馆图书借阅与管理的系统。包含以下功能：

---

### ✅ 1. 功能要求（建议功能顺序实现）

#### 🧾 A. 添加图书

* 用户输入图书名称（支持同时添加多本，空格分隔）。
* 添加到图书库（用集合或列表去重存储）。
* 添加成功后打印所有图书清单（按字母顺序）。

#### 🔍 B. 搜索图书

* 用户输入要搜索的图书名。
* 如果存在，显示“《XXX》在馆。”，否则显示“《XXX》不在馆。”

#### 🧑‍🤝‍🧑 C. 借书

* 用户输入要借的图书名。
* 如果该图书在图书库中，则将其从“在馆图书”移到“已借图书”。
* 否则提示该图书不存在或已被借出。

#### 📚 D. 归还图书

* 用户输入要归还的图书名。
* 如果该图书在已借列表中，则归还成功并移动回图书库。
* 否则提示“该书并未借出。”

#### 📊 E. 显示当前状态

* 打印当前“在馆图书”和“已借图书”列表，按字母顺序显示。

---

### ⚙️ 2. 技术要求

请尽量使用以下知识点实现：

* `print()` 和 `input()` 的不同用法
* 字符串拼接 `%` 或 `f"{}"` 格式化输出
* `split()` 处理用户输入多个图书
* `if/elif/else` 或 `match case` 实现命令调度
* 用 `while True:` 实现主循环，直到用户输入 `"exit"` 退出系统
* 使用 `list` 或 `set` 存储图书
* 使用 `sorted()` 对图书列表排序
* 可封装函数如 `add_books()`, `borrow_book()`, `return_book()` 等，提高模块化

---

### 🧪 3. 示例交互（仅供参考）

```text
欢迎来到图书馆管理系统！
请输入指令（add/search/borrow/return/show/exit）: add
请输入要添加的图书（以空格分隔）: 红楼梦 西游记 水浒传
添加成功！当前图书库：
['水浒传', '西游记', '红楼梦']

请输入指令（add/search/borrow/return/show/exit）: borrow
请输入要借的图书名: 红楼梦
您已成功借出《红楼梦》

请输入指令（add/search/borrow/return/show/exit）: show
在馆图书：['水浒传', '西游记']
已借图书：['红楼梦']

请输入指令（add/search/borrow/return/show/exit）: return
请输入要归还的图书名: 红楼梦
《红楼梦》归还成功！

请输入指令（add/search/borrow/return/show/exit）: exit
系统已退出。
```

---

### 🌟 4. 加分挑战（选做）

* 支持记录图书借阅次数并按次数排序
* 用字典代替列表储存图书信息，例如：`{'红楼梦': '在馆', '西游记': '在馆', '水浒传': '借出'}`
* 实现保存借阅记录，如 `借书人名 + 图书 + 时间`（用`input()`输入）

'''




book_exist = []  
book_borrowed = []
print('欢迎来到图书馆管理系统！')
while True:
    command = input('请输入指令(add/search/borrow/return/show/exit):')
    match command:
        case 'add':
            add = input('请输入要添加的图书（以空格分隔）')
            book_exist = book_exist + add.split()
        case 'search':
            search = input('请输入您要查询的一本书：')
            if search in book_exist:
                print(f'《{search}》在馆')
            else:
                print(f'《{search}》不在馆')
        case 'borrow':
            borrow = input('请输入要借的图书名:')  #如果没有要提示
            book_exist.remove(borrow)
            book_borrowed.append(borrow)
            print(f'您已成功借出{borrow}')
        case 'return':
            returns = input('请输入要归还的图书名:')  #如果没有要提示
            book_exist.append(returns)
            book_borrowed.remove(returns)
            print(f'《{returns}》归还成功！')
        case 'show':
            print(f'在馆图书：{book_exist}')
            print(f'已借图书：{book_borrowed}')
        case 'exit':
            break
        case _ :
            continue


