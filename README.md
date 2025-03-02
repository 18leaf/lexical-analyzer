TOKEN SET COMMENT

	Token Set -> For projectpart1

		KEYWORDS -> only from example code for now
			PYTHON -> see identifiers logic
				def,

			JAVA
				public, class, static, void, int, String


		IDENTIFIERS -> rules
			PYTHON -> from https://www.geeksforgeeks.org/python-tokens-and-character-sets/#
				START WITH:   a-Z or _
				CAN HAVE: 0-9, a-Z, _, (digits cannot be first letter)
				CAN NOT BE: keyword

				IS CASE SENSITIVE

				LOGIC:
				if first of this is a-Z or _
					until this ends (punctuation OR whitespace)
						check for digits, letters, _
					check in keyword

			JAVA -> from https://www.geeksforgeeks.org/java-tokens/
				START WITH: a-Z or _
				CAN HAVE: 0-9, _, a-Z



		LITERALS
			PYTHON ** not needed for this project
				Numerical
					integer, float,

				String/Char
					start with ' or ", end with " or '


			JAVA
				Numeric
					Integer: start with 0-9 and has only digits
					Decimal: start with either 0-9 OR . and contains only 1 decimal

		OPERATORS:
			PYTHON:
				=, +

			JAVA
				=, +


		PUNCTUATION:
			PYTHON
				(, ), ,, :,

			JAVA
			{, }, (, ), [, ], ,, ;


		REQUIREMENTS:
			PYTHON
				def add_numbers(num1, num2):
					sum = num1 + num2
					print('Sum: ',sum)

			JAVA
				public class JavaExample {

				  public static void main(String[] args) {

					int num1 = 5, num2 = 15,sum;

				sum = num1+num2;

				System.out.println("Sum of "+num1+" and "+num2+" is: "+sum);

				  }

				}
	TOKEN SET