### The Algorithm 
In this assignment we were required to implement the Karatsuba multiplication algorithm. The function I implemented for doing this takes in 3 inputs, I1, I2 and b. The function mulitplies I2 and I1 where b is the base of the two numbers.
The karatsuba algorithm works by taking advantage of the following fact.
Let \(x,y\) be n-digit integers in base B. For any positive integer m less than n, one can write the two given numbers as, \
$$x = x_{1}^{m} + x_0 $$ 
$$y = y_{1}^{m} + y_0 $$
Where $x_1 \text{ and } y_1$ are the first halves of the integers and $x_0$ and $y_0$ are the second halves. \
Then \
$$xy = (x_{1}^{m} + x_0)(y_{1}^{m} + y_0) $$
$$= x_1y_1B^{2m} + (x_1y_0 + x_0y_1)B^m + x_0y_0 $$
Karatsuba's insight was that $x_1y_0 + x_0y_1$ can be written in terms of $x_1y_1$ and $x_0y_0$, thus saving a multiplication step. This is shown below:
$$x_1y_0 + x_0y_1 = (x_1 + x_0)(y_1 + y_0) - x_1y_1 - x_0y_0$$

The algorithm is implemented recursively where you recursively call the karatsuba_mulitply function on smaller inputs until you get the the base case and can apply primitive multiplication to digits of length 1. 
### Challenges 
When implementing this algorithm I ran into the following problem. The stoi() function in c++ outputs an integer in base 10. This meant that I could not do the primitive calculations in base 10 and then convert them back to the input base.
As such, I wrote helper functions which convert strings to and from digits for a given base b. I also wrote a helper function to convert from a base b to base 10 and vice versa. This allowed me to do the primitive calculations in base 10.
