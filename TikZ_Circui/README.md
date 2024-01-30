# TikZ-Circui Generator

This is what we expect the workflow to look like

- Draw a circuit sketch yourself (or have a basic idea of composition in mind)
- Write the basic requirements and requirements in a txt file
- Execute it with this C program (TikZ-Circuit Generator) to generate a TikZ code
- Generate a pdf file with your own compiler (or directly on Overleaf) to get the finished product.

## Digital circuits

How the digital circuit generator is compiled
```
gcc TikZ_gen.c TikZ_gen_func.c -o TikZ_gen
```
Which should be written like this in the txt file.
```
< that are marked with the starting point (that is, the line number corresponding to each line)>, <Circuit elements> <direction> <line state> < optional, (the end node) > < (optional,comment, with curly braces).
... (Every line is such a standard)
```

There are things to pay attention to:
- The starting point is the end of the inherited previous component.

- If it is only a line representing a circuit,`<Circuit elements>` fill in 'line'

- The direction is `l` for left, `r` for right, `u` for up, and `d` for down, which refers to the direction of the circuit and is relative to the starting point.

- The beginning and end states of the line are, for example, a solid circle at the beginning of the line and a hollow circle at the end of the line. The solid is represented by *, while the hollow is represented by o, and there is no can __NOT__ be left unwritten!

- The text of the callout is marked with curly braces, e.g. '{nnp}' indicates the abbreviation of the circuit component. If you select Annotation Text, you can select the annotation direction of the text (you only need to add {_} to indicate the opposite of the default, for example, it is originally marked on the left, and optionally on the right)

A standard line input should look like this

```
0 R r o- {R_1}
```
The abbreviation of each component of the circuit (i.e., the `<Circuit elements>` entered in the txt file)
```
- R Ordinary Resistor
- C capacitors
- L Inductance
- vC voltage capacitors
- vR varistor resistors
- GND grounding
```



# TikZ-Circui 生成器

我们期望的工作流应该是这样的

- 自己画好一个电路学草图（或者心里有构图的基本思路）
- 将基本的需求和要求用txt文件写入
- 用这个C语言程序（TikZ-Circuit生成器）执行，生成一个TikZ代码
- 用自己的编译器（或者直接在Overleaf上编译）生成一个pdf文件，得到成品。

## 数字电路

数字电路生成器的编译方式

```
gcc TikZ_gen.c TikZ_gen_func.c -o TikZ_gen
```

其中在txt文件中应该像下面这样写入。
```
<起始点（即对应每一行的行号）> <电路元件> <方向> <线的始末状态> <(可选的末尾节点)> <(可选的，需要用大括号标注)标注的文字>
...(每一行都是这样的标准)
```
需要注意的有
- 起始点是继承上一个元件的末端。

- 如果只是表示电路的线，`<起始电路元件>`填入`line`

- 其中的方向用`l`表示左、`r`表示右、`u`表示上、`d`表示下，他们是指电路的线路朝向,是相对起始点而言的。

- 线的始末状态是指，例如线的开头是实心的圆圈，线的末尾是空心的圆圈。其中实心用\*表示，而空心则用o表示,没有则直接写`-`。

- 标注的文字用大括号标注，例如`{nnp}`表示电路元件的简称。如果选择标注文字，可以选择文字的标注方向(只需要添加{_}表示和默认相反，例如本来标注在左边，加上可选参数则标注在右边)


一个标准的行输入应该是这样

```
0 R r o- {R_1}
```

其中电路各个元件的简称（即在txt文件输入的`<电路元件>`）
```
- R 普通电阻
- C 电容
- L 电感
- vC 电压电容
- vR 变阻电阻
- gnd 接地
- bat 电池
- iso 电流源
- pbu 电源
- fld 实心发光二极管
- lamp 灯泡
```

---
### 新增特性

`op amp` 的行输入为
```
<起始点（即对应每一行的行号）> opa <方向> <线的始末状态> <(可选的末尾节点)> <(可选的，需要用大括号标注)标注的文字>
```


## 逻辑电路

---

