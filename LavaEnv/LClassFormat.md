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
| **B** | Big endian |
| **L** | Little endian |
| **U** | Unsigned |

## Header
The header is very tiny as it only describes the file as being an lclass file and what version of the file format it is.  
As this allows breaking the file format afterwards to allow better file formats in the future.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **LUI4** | **magicNumber** | The magic number of the lclass file format, it's value should always equal the string "**HOTL**" for Hot Lava. |
| **4** | **LUI2** | **formatVersion** | The version of the lclass file format, should be the value 1 for the version described here. |
| **6** | **LUI1** | **endianess** | The endianess of all integer types that don't specify their endianess in this lclass file.<br>*(0 is little endian, 1 is big endian)* |

## Constant Pool
The constant pool is a list of constant values to be used when parsing and linking the file.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI2** | **size** | The number of constants in the constant pool pluss 1. |
| **2** | **ConstantPoolEntry\[size-1]** | **entries** | The entries in the constant pool. |

## Constant Pool Entry
There are a couple of constant pool entry types, all of which start with the data below.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI1** | **tag** | A tag identifier for the constant pool entry. |

### **CLASS** Entry
A Class entry describes a class.  
**tag** = 1

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **1** | **UI2** | **nameEntry** | A **UTF8** entry in this constant pool which describes the name of this class entry. |

### **UTF8** Entry
A UTF8 entry describes a UTF-8 encoded string.
**tag** = 2

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **1** | **UI4** | **length** | The length of this UTF-8 encoded string. |
| **5** | **UI1\[length]** | **string** | The actual string. |

## Class Information
The class information stores necessary information about the class.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI2** | **classFlags** | Flags describing this class. |
| **2** | **UI2** | **flags** | A **CLASS* entry in the constant pool which describes this class. |
| **4** | **UI2** | **superCount** | The number of super classes. |
| **6** | **UI2\[superCount]** | **supers** | The supers of this class. |
| **?** | **UI2** | **fieldCount** | The number of fields in this class. |
| **?** | **Field\[fieldCount]** | **fields** | The fields of this class. |
| **?** | **UI2** | **methodCount** | The number of methods in this class. |
| **?** | **Method\[methodCount]** | **methods** | The methods of this class. |
| **?** | **UI2** | **attributeCount** | The number of attributes in this class. |
| **?** | **Attribute\[attributeCount]** | **attibutes** | The attributes of this class. |

## Field
The field struct stores necessary information about a field in the class.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI2** | **flags** | Flags describing this field. |
| **2** | **UI2** | **idEntry** | A **UTF8** entry in the constant pool which describes this field's id. |
| **4** | **UI2** | **attributeCount** | The number of attributes in this field. |
| **6** | **Attribute\[attributeCount]** | **attibutes** | The attributes of this field. |

## Method
The method struct stores necessary information about a method in the class.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI2** | **flags** | Flags describing this field. |
| **2** | **UI2** | **idEntry** | A **UTF8** entry in the constant pool which describes this method's id. |
| **4** | **UI2** | **attributeCount** | The number of attributes in this method. |
| **6** | **Attribute\[attributeCount]** | **attibutes** | The attributes of this method. |

## Attribute
The attribute struct stores ncessary information about an attribute in the class, field or method.

| Offset | Type | Name | Description |
| :---: | :---: | --- | --- |
| **0** | **UI2** | **nameEntry** | A **UTF8** entry in the constant pool which describes this attribute's name |
| **2** | **UI4** | **attributeLength** | The length of this attribute. |
| **6** | **UI1\[attributeLength]** | **data** | The data of this attribute. |
