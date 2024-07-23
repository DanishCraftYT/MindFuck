# Overview

# basic operators

## +
increments a element in the array.<br>

## -
decrements a element in the array.<br>

## >
goes to the next element in the array.<br>

## <
goes to the previous element in the array.<br>

# printing to console

## .
prints the letter from the current element.<br>

## .&
prints the position of the current element in the array. this can be useful when debugging.<br>

## .!
prints the number the letter from the current element represents. this can be useful when debugging.<br>

# while loops

while loops requires you to manually decrease the iterator everytime it begins or ends a iteration.<br>

while loops use square brackets: "[]". the iterator will always be the current element.<br>
example:<br>
+++++++<br>
[ // runs the loop 7 times<br>
	->+++++++++<<br>
]> // goes to the element we incremented a bunch of times in the while loop<br>
..! // prints the letter the element contains then the number that the letter represents in UTF-8. in this case it should print:<br>
"<br>
?<br>
63<br>
"<br>

# for loops

for loops will keep a reference to the iterator so you can change the element without having to worry about infinite loops
however it should be noted that it's not the case for nested for loops as they will run multiple times so any change in the
iterator could result in the for loop running more or less times than intended next time the nested for loop executes.<br>

for loops use curly brackets: "{}". the for loops will copy the current element and use it as a iterator.<br>
example:<br>
++++++<br>
{ // runs for loop 6 times<br>
	+++++<br>
}<br>
..! // prints the letter the element contains then the number the letter represents in UTF-8. in this case it should print:<br>
"<br>
(<br>
41<br>
"<br>
