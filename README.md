<html>

# C语言学习 1
## 1、按位取反操作符号、数据以补码的形式存储；
## 2、static：
            静态局部变量，在程序的生命周期中保持存在，不需要在每次它进入和离开作用域时进行创建和销毁；
            静态全局变量，作用域只能是声明变量的文件范围内；
## 3、函数的宏定义：#define Max(x, y) (x > y ? x : y)        
## 4、指针：
```
            int* p;   //定义int类型的指针变量p
            int a=10;
            p=&a;   //&取地址操作符号
            *p=11;  //*为解引用操作符号，通过地址指向a
            printf("%p\n",p);  //以%p地址的形式输出；
```    

# C语言学习 2
## 1、中文的编码：
            GBK采用双字节表示，总体编码范围为8140-FEFE，首字节在81-FE 之间，尾字节在40-FE 之间，
            剔除 xx7F一条线。总计126*190=23940 个码位，共收入21886个汉字和图形符号，
            其中汉字（包括部首和构件）21003 个，图形符号883 个；

            将中文字符以整形输出两个数字，获得是两个负数，第一个数字是该字符编码首字节-256，第二个数字是该字符编码尾字节-256；
## 2、 结构类型：
            基本形式：
```
             struct People
            {
                char name[20];
                char sex[2];   //中文占两个字节
                int age;
            };
```
## 3、if(3==i)  好的代码风格，数字放在前面，常量放在后面。当漏写一个=时，编译器能够检测出来；
## 4、witch语句：
            switch可以嵌套使用，if可以在switch中使用；
            执行一个case后没有break会继续执行下一个case，直到break或者执行完所有case；
            defaul可以放在任意位置，建议放在最后面，与我们的逻辑相符；
## 5、break：直接跳出循环；
    ##6、continue：终止本次循环，continue后面的语句不再执行，进入下一次循环的入口判断；
## 7、键盘输入CTRL+Z，getchar就会获得EOF，不然getchar一次只能获得一个字节
            ```
            while((c=getchar())!=EOF ) 
            {
                putchar(c );
            }
            ```

# C语言的学习 3
## 1、输入缓冲区：
            scanf只读取输入缓冲区数据第一个空格之前的字符，执行scanf语句后，清空输入缓冲区以免影响到后面的读取操作
```
            while ((k = getchar()) != '\n')//读取输入缓冲区第一个空格之后的所有数据
            {
                ;
            }    //清空输入缓冲区;
```
## 2、一次性从键盘获得有空格的字符串的方法：
```
            while((str=getchar())!='\n')
            {
                arr1[len] = str;
                len++;
            };
```
## 3、二分查找\折半查找：适用于有序排列  时间复杂度为log2（n）
## 4、阶乘：
```
            int all = 0; //让1的阶乘等于1+0
            int io = 1;  //让1的阶乘等于1*1
            for (i = 1; i <= val; i++)
            {
                io = io * i;   //i的阶乘
                all = all + io;  //1~i阶乘的和
                printf("<%d的阶乘为%d>  ",i,io);
            };
```
## 5、字符串的大小    
            整个字符串的大小除以单个字符的大小 等于 字符串的实际长度加1
            sizeof(str)/sizeof(str[0]) == strlen(str)+1
            字符串的末尾还有隐藏的结束标志符'\n';
    
</html>