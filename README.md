# MD2HTML

a C implementation of the Markdown to HTML system with code highlighting support.

## Supported

* `Customized CSS`
* `Headers` ( from # to #### )
* `Part Separator`( --- ).
* `Link` ( (name)[url] )
* `Blockquote` ( > )
* `Image` ( !(name)[url] )
* `Italic Style` ( *some text* )
* `Bold Style` ( **some text** )
* `Code` ( ` some text ` )
* `Code Block` ( '\t' some text )
* `List` ( * item )
* <sup>new!</sup> Support code highlighting with 2 styles(C, C++)

![code style](./img/code-style.png)


## ToDo

* and so and forth

##Examples

#### Headers:
	# 1st header
	## 2nd header
	### 3rd header
	#### 4th header
	##### 5th header
	###### 6th header

#### Part Separator:
	---
	----

#### Links:
	[name](example.com/)

#### Quotes:
	> quotes
	> quotes

#### Images:
	![name](example.com/pic.jpg)

#### Inline formating:
	**bold test** and *italics*.
	
#### Code:
	`some code`
	
#### Code Block:
		some code
		some code
	
#### Lists:
	* item1
	* item2
