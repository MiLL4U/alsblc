# Asynmetric Least Squares Baseline Correction
Baseline correction using asymmetric least squares, accelerated with C++.

Asymmetric least squares method is a technique that can correct the baseline while adjusting the balance between the **fit** of the baseline to the spectrum and the **smoothness** of the baseline curve.

## Dependencies
- [Eigen](https://eigen.tuxfamily.org/) (C++ template library for linear algebra)
- [pybind11](https://github.com/pybind/pybind11) (Seamless operability between C++11 and Python)
- [NumPy](https://numpy.org/) (Fundamental package for scientific computing with Python)

## Principle
In ALS, the baseline
$\mathbf{Z}=\lbrace z_1, z_2, \cdots, z_n \rbrace$
for the spectrum
$\mathbf{Y}=\lbrace y_1, y_2, \cdots, y_n \rbrace$
is determined to minimize the function:

```math
F(\mathbf{Z}) =
    \sum_iw_i(y_i-z_i)^2 +
    \lambda\sum_i(\Delta^2z_i)^2
```

where the weights $w_i$ are used to treat each point of the spectrum asymmetrically, with a small value $p$ (such as 0.001) given by:

```math
w_i = \left\{
    \begin{array}{ll}
        p & (y_i \geq z_i) \\
        1-p & (y_i \lt z_i)
    \end{array}
\right.
```

This prioritizes points where the spectrum falls below the baseline $(y_i < z_i)$ in fitting, causing the baseline to fall below the spectrum. $\Delta^2$ represents the second derivative (numerical derivative) of the spectrum and is calculated as:

```math
\begin{aligned}
\Delta^2z_i & = (z_i - z_{i-1}) - (z_{i-1} - z_{i-2}) \\
& = z_i - 2z_{i-1} + z_{i-2}
\end{aligned}
```

The first term of $F(\mathbf{Z})$ represents the difference between the spectrum and the baseline, while the second term serves as a penalty term representing the complexity of the baseline curve, with the constant $\lambda$ determining its scale. Setting $\lambda$ to a small value yields a complex baseline curve, while a large value yields a smooth baseline curve.
### References
[P.H.C. Eilers, _Anal. Chem._, **2004**, _76_, 404-411.](https://pubs.acs.org/doi/10.1021/ac034800e)

## Algorithm
The algorithm for baseline calculation using ALS is as follows. First, initialize all the weights $\mathbf{w}=\lbrace w_1, w_2, \cdots, w_n \rbrace$ to 1. Then update the baseline $\mathbf{Z}$ and weights $\mathbf{w}$ iteratively:

```math
\begin{array}{ll}
\mathbf{Z}\leftarrow\mathop{\rm arg~min}\limits_{\mathbf{Z}}\bigg\lbrace
    \sum_iw_i(y_i-z_i)^2 +
    \lambda\sum_i(\Delta^2z_i)^2
\bigg\rbrace & (1) \\ \\

w_i\leftarrow\left\{
    \begin{array}{ll}
        p & (y_i \geq z_i) \\
        1-p & (y_i \lt z_i)
    \end{array}
\right. & (2)
\end{array}
```
 until convergence.

$F(\mathbf{Z})$ can be expressed using matrices and vectors as:
```math
F(\mathbf{Z}) = (\mathbf{Y}-\mathbf{Z})^T\mathbf{W}(\mathbf{Y}-\mathbf{Z}) +
                \lambda\mathbf{Z}^T(\mathbf{D}^T\mathbf{D})\mathbf{Z}
```
where $\mathbf{W}$ is a diagonal matrix with the weights $\mathbf{w}$ as its diagonal elements, and $\mathbf{D}$ is an $(n-2)×n$ matrix such that $\mathbf{DZ} = \Delta^2\mathbf{Z}$, defined as:
```math
\mathbf{D} = \begin{pmatrix}
     1 & -2 &  1 &  0 &  0 & \cdots &  0 &  0 &  0 &  0 &  0 \\
     0 &  1 & -2 &  1 &  0 & \cdots &  0 &  0 &  0 &  0 &  0 \\
    & & & & & \vdots  \\
     0 &  0 &  0 &  0 &  0 & \cdots &  0 &  1 & -2 &  1 &  0 \\
     0 &  0 &  0 &  0 &  0 & \cdots &  0 &  0 &  1 &  -2 &  1 \\
\end{pmatrix}
```
For equation $(1)$, the baseline $\mathbf{Z}$ is obtained when the partial derivative of $F(\mathbf{Z})$ with respect to $\mathbf{Z}$:
```math
\frac{\partial F(\mathbf{Z})}{\partial \mathbf{Z}}
 = -2\mathbf{W}(\mathbf{Y}-\mathbf{Z}) + 2\lambda(\mathbf{D}^T\mathbf{D})\mathbf{Z}
```
 is zero which occurs when:
```math
(\mathbf{W} + \lambda \mathbf{D}^T\mathbf{D})\mathbf{Z} = \mathbf{WY}
```
and thus, the baseline $\mathbf{Z}$ is given by:
```math
\mathbf{Z} = (\mathbf{W} + \lambda \mathbf{D}^T\mathbf{D})^{-1}\mathbf{WY}
```
### References

[P.H.C. Eilers, _Anal. Chem._, **2003**, _75_, 3631-3636.](https://pubs.acs.org/doi/10.1021/ac034173t)


## Installation

## Usage

