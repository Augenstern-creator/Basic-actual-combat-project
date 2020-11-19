# 定义功能界面函数
def info_print():
    print('-------------请选择功能-----------------')
    print('1.添加学员')
    print('2.删除学员')
    print('3.修改学员')
    print('4.查询学员')
    print('5.显示所有学员')
    print('6.退出系统')
    print('-' * 20)
    
# 等待存储所有学员的信息
info = []

# 1.添加学员信息函数
def add_info():
    """添加学员函数"""
    # 1.用户输入
    new_id = input('请输入学号：')
    new_name = input('请输入姓名：')
    new_tel = input('请输入手机号：')
    # 2.判断是否添加这个学员：如果学员姓名存在则报错提示
    global info
    # 2.1 判断用户输入的姓名和列表里面的字典的name对应的值相等
    for i in info:
        if new_name == i['name']:
            print('此用户已经存在')
            return
    # 2.2如果用户输入的姓名不存在，则添加学员信息
    info_dict = {}
    # 将用户输入的数据追加到字典
    info_dict['id'] = new_id
    info_dict['name'] = new_name
    info_dict['tel'] = new_tel

    #将这个学员的字典数据追加到列表
    info.append(info_dict)
    print(info)


# 2.删除学员函数
def del_info():
    """删除学员"""
    # 1.用户输入要删除的学生姓名
    del_name = input('请输入要删除的学员姓名：')
    # 2.判断学员是否存在，存在则删除，不存在提示
    # 2.1 声明info是全局变量
    global info
    # 2.2 遍历列表
    for i in info:
      # 2.3判断学员是否存在，存在则执行删除(列表里面的字典)
        if del_name == i['name']:
            info.remove(i)
            break
    else:
        # 如果遍历了所有数据，还是没有执行删除操作，则学员不存在
        print('该学员不存在')


# 3.修改学员函数
def modify_info():
    """修改学员信息"""

    # 用户输入要修改的学员姓名
    modify_name = input('请输入要修改的学员姓名:')

    # 判断学员是否存在：存在则修改
    global info

    for i in info:
        if modify_name == i['name']:
            # 将tel这个key修改，并终止此循环
            i['tel'] = input('请输入新的手机号：')
            break
    else:
        print('学员不存在')

    # 打印info
    print(info)



# 4.查询学员信息函数
def search_info():
    """查询学员信息"""
    # 1.用户输入学员姓名
    search_name = input('请输入要查询的学员的姓名：')

    # 2.检查学员是否存在
    global info

    for i in info:
        if search_name == i['name']:
            print('查询到的学员信息如下')
            print(f"学员的学号是{i['id']},姓名是{i['name']},手机号是{'i[tel'}")
            break
    else:
        print('查无此人')


# 5.显示学员函数
def print_all():
    """显示所有学员信息"""
    print('学号\t姓名\t手机号')
    for i in info:
        print(f"{i['name']},{i['name']},{i['tel']}")

# 系统功能循环使用，直到用户输入6才退出循环
while True:
    # 1.显示功能界面
    info_print()

    # 2.用户输入功能序号
    user_num = int(input('请输入功能序号：'))
    # 3.按照用户输入的功能序号，执行不同的功能(函数)
    if user_num == 1:
        print('添加学员')
        add_info()
    elif user_num == 2:
        print('删除学员')
        del_info()
    elif user_num == 3:
        print('修改学员')
        modify_info()
    elif user_num == 4:
        print('查询学员')
        search_info()
    elif user_num == 5:
        print('显示所有学员')
        print_all()
    elif user_num == 6:
        print('退出系统')
        # 终止退出while:True ,break
        exit_flag = input('确定退出吗?yes or no:')
        if exit_flag == 'yes':
            break
    else:
        print('输入错误，请重新输入')
