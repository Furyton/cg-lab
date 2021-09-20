# experiments

在对应文件夹中提交你的代码和说明文档，在文档中说明你实现的功能，展示你的实验结果。

## 实验0

本次实验要求你熟悉OpenGL的配置和使用，

1. 读取三角形网格数据文件
2. 使用 OpenGL 绘制该模型(能够对模型进行平移、旋转)
3. 交互设定模型的两个位置和姿态，利用**四元数** (quaternion) 对物体进行平滑的移动和旋转，使得物体在平移过程中能够平滑旋转。

（推荐使用 OpenGL 的固定功能管线，搭配GLUT库，操作比较简便。）

（如果你想挑战一下自己，实现更“现代”的效果，则需要配置OpenGL的core profile，自己编写Shader程序，参考[Learn OpenGL](https://learnopengl.com/Getting-started/OpenGL).）

## 实验1

本实验要求实现层次结构, 实现一个火柴人的走路动作。要求至少要在实验中画出火柴人的如下结构:

![火柴人结构](/images/01.png)

层次结构建模适用于机器人等应用程序，其中对象的动态行为由模型各部分之间的关系来表征。 我们可以用图抽象和直观地表示模型各部分之间的关系。 在数学上，图由一组节点（或多个顶点）和一组边组成。 边连接一对节点，或将一个节点与其自身相连。边也可以具有方向。这里使用的最重要的图的类型是树，用来表示物理模型关系。

## 实验2

编写一个**光线追踪**渲染程序（下图仅供参考）。
![光线追踪](https://raytracing.github.io/images/img-1.21-book1-final.jpg)

1. 基本要求是实现阴影和物体间反射，另外鼓励任何额外的扩展
2. 利用实验0的程序绘制同样的场景，比较与实验0的绘制效果

（可以参考[Ray Tracing in One Weekend](https://raytracing.github.io/).） 

（如果你想要挑战自己，实现GPU加速的光线追踪，可以使用OpenGL中的Shader来实现上述功能。） 

（简单的光线追踪能够实现阴影、反射、折射等效果，但不能保证物理准确性。而更高级的光线追踪算法（如**路径追踪**）结合**基于物理的双向散射分布函数**(BSDF)，能够实现**基于物理的渲染**(PBR)，进一步提升渲染的真实感。如果你对此感兴趣，可以参考[光线追踪渲染器示例Nori](https://github.com/wjakob/nori)，以及[Physically Based Rendering: From Theory To Implementation](https://www.pbr-book.org/3ed-2018/contents).）

## 实验3

本次实验的内容主要为：绘制下面三种形状。

1. 贝塞尔曲线的绘制
2. Surfaces of revolution
3. Sweep Surfaces

![示意图](/images/02.png)
