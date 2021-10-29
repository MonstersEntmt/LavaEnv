# LClass V1 file format specification
This markdown file describes the format of an `.lclass` file.  
The file format of `.lclass` has a striking ressemblence of Java's `.class` file format.

This spec file uses the following types:
| Type | Bytes |
| :---: | :---: |
| _es_**I1** | 1 |
| _es_**I2** | 2 |
| _es_**I4** | 4 |
| _es_**I8** | 8 |

_es_**I1** uses _e_ and _s_ as specifiers and are:
| Char | Description | Valid values |
| :---: | --- | --- |
| *e* | Endianess | **B**, **L**, empty |
| *s* | Sign | **U**, empty |

And the capital letters **I**, **B**, **L** and **U** are:
| Char | Description |
| :---: | --- |
| **I** | Integer |
| **B** | Big endianess |
| **L** | Little endianess |
| **U** | Unsigned |

## Header
The header is very tiny as it only describes the file as being an lclass file and what version of the file format it is.  
As this allows breaking the file format afterwards to allow better file formats in the future.

UI4 **magicNumber**: The magic number of the lclass file format, it's value should always equal the string "**HOTL**" for Hot Lava  
UI2 **formatVersion**: The version of the lclass file format, should be the value 1 for the version described here.

## Constant Pool
The constant pool is a list of constant values to be used when parsing and linking the file.

UI2 **size**: The number of constants in the constant pool + 1.  
ConstantPoolEntry[**size**-1] **entries**: The entries in the constant pool.

## Constant Pool Entry
There are a couple of constant pool entry types, all of which have the data below.  
The list of types are:
- **CLASS**: 1
- **UTF8**: 2

UI1 **tag**: The tag of the constant pool entry

For **CLASS**, **tag** has to be 1 and has the extra data below.

UI2 **nameIndex**: An index to a **UTF8** constant pool entry used to describe the name of the class.

For **UTF8**, **tag** has to be 2 and has the extra data below.

UI4 **length**: The length of the UTF8 encoded string.  
UI1[**length**] **string**: The actual string.

## Class Information
The class information stores necessary information about the class.

UI2 **classFlags**: Flags describing this class.  
UI2 **classEntry**: **CLASS** entry in the constant pool of this class.  
UI2 **superCount**: The number of super classes.  
UI2[**superCount**] **supers**: The supers of this class.  
UI2 **fieldCount**: The number of fields in this class.  
Field[**fieldCount**] **fields**: The fields of this class.  
UI2 **methodCount**: The number of methods in this class.  
Method[**methodCount**] **methods**: The methods of this class.  
UI2 **attributeCount**: The number of attributes in this class.  
Attribute[**attributeCount**] **attributes**: The attributes of this class.

## Field

UI2 **flags**: Flags describing this field.  
UI2 **idEntry**: **UTF8** entry in the constant pool describing the id of this field.  
UI2 **attributeCount**: The number of attributes in this field.  
Attribute[**attributeCount**] **attributes**: The attributes of this field.

## Method

UI2 **flags**: Flags describing this field.  
UI2 **idEntry**: **UTF8** entry in the constant pool describing the id of this method.  
UI2 **attributeCount**: The number of attributes in this method.  
Attribute[**attributeCount**] **attributes**: The attributes of this method.

## Attribute

UI2 **nameEntry**: **UTF8** entry in the constant pool describing the name of this attribute.  
UI4 **attributeLength**: The length of this attribute.  
UI1[**attributeLength**] **data**: The data of this attribute.
