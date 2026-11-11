# Comprehensive Trigonometry and Numerical Implementation Guide

## 1. Project Overview and Motivation

This repository serves as a theoretical reference and practical codebase for trigonometry, spanning from elementary geometric foundations to advanced analytical and numerical concepts.

### Primary Goals
- Implementation Excellence: To refine low-level, high-performance C and C++ implementations of mathematical functions, trigonometric algorithms, and numerical approximations.
- Educational Reference: To provide a structured, rigorous progression through trigonometry for study, research, and algorithmic application.
- Global Collaboration: To create an open-source framework where contributors across disciplines—graphics programming, physics engines, embedded systems, and pure mathematics—can collaborate, optimize implementations, and build robust mathematical utilities.

---

## 2. Foundations of Triangles

### 2.1 Basic Properties
A triangle is a three-sided polygon with three vertices and three internal angles.
- The sum of internal angles in Euclidean space is always $\pi$ radians ($180^\circ$):
  $$\alpha + \beta + \gamma = \pi$$
- Triangle Inequality: For side lengths $a$, $b$, and $c$:
  $$a + b > c, \quad a + c > b, \quad b + c > a$$

### 2.2 Right-Angled Triangles
In a right-angled triangle where one angle is $\frac{\pi}{2}$ ($90^\circ$), the side opposite to the right angle is the hypotenuse ($c$), and the remaining sides are the adjacent ($a$) and opposite ($b$) relative to an angle $\theta$.

#### The Pythagorean Theorem
$$a^2 + b^2 = c^2$$

---

## 3. Basic Trigonometric Functions

### 3.1 Right-Triangle Definitions
For an acute angle $\theta$:

$$\sin(\theta) = \frac{\text{Opposite}}{\text{Hypotenuse}}$$

$$\cos(\theta) = \frac{\text{Adjacent}}{\text{Hypotenuse}}$$

$$\tan(\theta) = \frac{\text{Opposite}}{\text{Adjacent}} = \frac{\sin(\theta)}{\cos(\theta)}$$

### 3.2 Reciprocal Functions
$$\csc(\theta) = \frac{1}{\sin(\theta)} = \frac{\text{Hypotenuse}}{\text{Opposite}}$$

$$\sec(\theta) = \frac{1}{\cos(\theta)} = \frac{\text{Hypotenuse}}{\text{Adjacent}}$$

$$\cot(\theta) = \frac{1}{\tan(\theta)} = \frac{\text{Adjacent}}{\text{Opposite}}$$

---

## 4. The Unit Circle and Radian Measure

### 4.1 Unit Circle Definition
Extending trigonometry beyond right triangles uses a circle of radius $r = 1$ centered at the origin $(0,0)$ in the Cartesian plane. An angle $\theta$ in standard position corresponds to a point $(x, y)$ on the circle:

$$x = \cos(\theta)$$
$$y = \sin(\theta)$$

### 4.2 Radians vs. Degrees
$$\theta_{\text{radians}} = \theta_{\text{degrees}} \cdot \frac{\pi}{180}$$

$$1 \text{ full rotation} = 2\pi \text{ radians} = 360^\circ$$

---

## 5. Fundamental Identities

### 5.1 Pythagorean Identities
$$\sin^2(\theta) + \cos^2(\theta) = 1$$
$$1 + \tan^2(\theta) = \sec^2(\theta)$$
$$1 + \cot^2(\theta) = \csc^2(\theta)$$

### 5.2 Angle Sum and Difference Formulas
$$\sin(\alpha \pm \beta) = \sin(\alpha)\cos(\beta) \pm \cos(\alpha)\sin(\beta)$$
$$\cos(\alpha \pm \beta) = \cos(\alpha)\cos(\beta) \mp \sin(\alpha)\sin(\beta)$$
$$\tan(\alpha \pm \beta) = \frac{\tan(\alpha) \pm \tan(\beta)}{1 \mp \tan(\alpha)\tan(\beta)}$$

### 5.3 Double-Angle and Half-Angle Formulas
$$\sin(2\theta) = 2\sin(\theta)\cos(\theta)$$
$$\cos(2\theta) = \cos^2(\theta) - \sin^2(\theta) = 2\cos^2(\theta) - 1 = 1 - 2\sin^2(\theta)$$
$$\sin^2\left(\frac{\theta}{2}\right) = \frac{1 - \cos(\theta)}{2}, \quad \cos^2\left(\frac{\theta}{2}\right) = \frac{1 + \cos(\theta)}{2}$$

---

## 6. Non-Right Triangle Trigonometry

### 6.1 Law of Sines
$$\frac{a}{\sin(A)} = \frac{b}{\sin(B)} = \frac{c}{\sin(C)} = 2R$$
where $R$ is the circumradius of the triangle.

### 6.2 Law of Cosines
$$c^2 = a^2 + b^2 - 2ab\cos(C)$$
$$b^2 = a^2 + c^2 - 2ac\cos(B)$$
$$a^2 = b^2 + c^2 - 2bc\cos(A)$$

### 6.3 Area of a General Triangle
$$\text{Area} = \frac{1}{2}ab\sin(C) = \sqrt{s(s-a)(s-b)(s-c)}$$
where $s = \frac{a+b+c}{2}$ (Heron's Formula).

---

## 7. Inverse Trigonometric Functions

Inverse functions resolve the angle $\theta$ given a ratio value:

$$\arcsin(x) : [-1, 1] \to \left[-\frac{\pi}{2}, \frac{\pi}{2}\right]$$
$$\arccos(x) : [-1, 1] \to [0, \pi]$$
$$\arctan(x) : (-\infty, \infty) \to \left(-\frac{\pi}{2}, \frac{\pi}{2}\right)$$
$$\text{atan2}(y, x) : \text{computes } \arctan\left(\frac{y}{x}\right) \text{ taking quadrant signs into account.}$$

---

## 8. Hyperbolic Functions

Analogous to circular functions, hyperbolic functions are defined via exponential functions $e^x$:

$$\sinh(x) = \frac{e^x - e^{-x}}{2}$$

$$\cosh(x) = \frac{e^x + e^{-x}}{2}$$

$$\tanh(x) = \frac{\sinh(x)}{\cosh(x)} = \frac{e^x - e^{-x}}{e^x + e^{-x}}$$

### Hyperbolic Identity
$$\cosh^2(x) - \sinh^2(x) = 1$$

---

## 9. Advanced Analysis and Complex Variables

### 9.1 Euler's Formula
$$e^{i\theta} = \cos(\theta) + i\sin(\theta)$$

### 9.2 De Moivre's Theorem
$$(\cos(\theta) + i\sin(\theta))^n = \cos(n\theta) + i\sin(n\theta)$$

### 9.3 Infinite Series Representation (Taylor / Maclaurin)
$$\sin(x) = \sum_{n=0}^{\infty} \frac{(-1)^n x^{2n+1}}{(2n+1)!} = x - \frac{x^3}{3!} + \frac{x^5}{5!} - \frac{x^7}{7!} + \dots$$

$$\cos(x) = \sum_{n=0}^{\infty} \frac{(-1)^n x^{2n}}{(2n)!} = 1 - \frac{x^2}{2!} + \frac{x^4}{4!} - \frac{x^6}{6!} + \dots$$

---

## 10. Computational Methods and C/C++ Implementation Strategies

Implementing trigonometric functions from scratch requires efficient numerical algorithms balancing speed, precision, and hardware limits.

### 11.1 Polynomial Approximations
- Taylor Series: Simple to construct, but converges slowly near boundaries like $\frac{\pi}{2}$.
- Chebyshev Polynomials & Minimax Approximations: Used in production math libraries (such as `libm`) to minimize maximum approximation error over a specified interval.

### 11.2 The CORDIC Algorithm
Coordinate Rotation Digital Computer (CORDIC) is an iterative algorithm that computes trigonometric functions using only shift and add operations, making it useful for microcontrollers and hardware lacking dedicated floating-point units.

### 11.3 C/C++ Implementation Roadmap
1. Range Reduction: Reduce input $x$ to a standard fundamental domain such as $[0, \frac{\pi}{4}]$.
2. Core Evaluation: Use polynomial evaluation (Horner's Method) or CORDIC iterations.
3. Sign Correction: Reconstruct output based on original quadrant.
4. Performance Optimization: Utilize SIMD vectors (AVX, NEON) and lookup tables for high-throughput computing.

---

### Contribution Guidelines
Contributions to both theory documentation and C/C++ implementations are welcome:
1. Benchmark any new C/C++ implementations against standard `math.h` / `<cmath>` routines.
2. Maintain high precision and document numerical error bounds ($\text{ULP}$ analysis).
3. Ensure compatibility with C99, C++17, and standard cross-platform compilers (`gcc`, `clang`, `msvc`).
