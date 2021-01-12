# viterbi
The [Viterbi algorithm](https://en.wikipedia.org/wiki/Viterbi_algorithm) is a dynamic programming algorithm to find optimal paths in the hidden space of an hidden Markov model. 
It has wide applications, including for Natural Language Processing tasks such as Part-of-Speech tagging.
Problem and algorithm descriptions are given below.

#### Example
Compile and link `example.cpp` and `viterbi.cpp`, e.g.:

```
$ g++ example.cpp viterbi.cpp -o example
$ ./example
```

You will be prompted to insert the data defining the model, and the input path in observable space.

#### Problem
Let <img src="https://render.githubusercontent.com/render/math?math=\mathscr M = (\mathscr H, \mathscr O, T, E, \pi)"> be an hidden Markov model, where:
  - <img src="https://render.githubusercontent.com/render/math?math=\mathscr H = \{h_1, h_2, \cdots, h_{p}\}">: hidden space of finite cardinality <img src="https://render.githubusercontent.com/render/math?math=p">
  - <img src="https://render.githubusercontent.com/render/math?math=\mathscr O = \{o_1, o_2, \cdots, o_{q}\}">: observable space of finite cardinality <img src="https://render.githubusercontent.com/render/math?math=q">
  - <img src="https://render.githubusercontent.com/render/math?math=T_{ij} = \text{Prob}(h_i \leftarrow h_j)">: transition matrix
  - <img src="https://render.githubusercontent.com/render/math?math=E_{ij} = \text{Prob}(o_i \leftarrow h_j)">: emission matrix
  - <img src="https://render.githubusercontent.com/render/math?math=\pi_{i} = \text{Prob}(h_i \leftarrow \emptyset)">: start probabilities

Given a path 
<img src="https://render.githubusercontent.com/render/math?math=Y=y_1y_2\cdots y_L"> in observable space, 
find a corresponding path 
<img src="https://render.githubusercontent.com/render/math?math=X=x_1x_2\cdots x_L"> in hidden space
maximizing the conditional probability <img src="https://render.githubusercontent.com/render/math?math=\text{Prob(X | Y)}">
or, equivalently, the joint probability <img src="https://render.githubusercontent.com/render/math?math=\text{Prob(X,Y)}">

#### Algorithm
The [Viterbi algorithm](https://en.wikipedia.org/wiki/Viterbi_algorithm) is a dynamic programming procedure to solve the problem above. It is based on the optimization subproblems:

<img src="https://render.githubusercontent.com/render/math?math=\mathscr{P}_{il}=\max_{x_{1}x_{2}\cdots x_{l-1}}\text{Prob}(x_{1}x_{2}\cdots x_{l-1}x_{l},\,y_{1}y_{2}\cdots y_{l-1}y_{l})">

<img src="https://render.githubusercontent.com/render/math?math=\mathscr{X}_{il}=\arg\max_{x_{l-1}}\max_{x_{1}x_{2}\cdots x_{l-2}}\text{Prob}(x_{1}x_{2}\cdots x_{l-1}x_{l},\,y_{1}y_{2}\cdots y_{l-1}y_{l})">

which can be solved recursively.
