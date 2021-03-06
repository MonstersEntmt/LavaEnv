# LClass V1 file format specification
This markdown file describes the format of an `.lclass` file.  
The file format of `.lclass` has a striking ressemblence of Java's `.class` file format.

## Used Types
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

| Type | Name | Description |
| :---: | --- | --- |
| **LUI4** | **magicNumber** | The magic number of the lclass file format, it's value should always equal the string "**HOTL**" for Hot Lava. |
| **LUI2** | **formatVersion** | The version of the lclass file format, should be the value 1 for the version described here. |
| **[EEndianess](#eendianess)** | **endianess** | The endianess of all integer types that don't specify their endianess in this lclass file. |
| **[Body](#body)** | **body** | The body of the file. |

### **EEndianess**
Type = **LUI1**
| Value | Name | Description |
| :---: | --- | --- |
| **0** | **Little** | Little endian |
| **1** | **Big** | Big endian |

## Body
The body is the large part of the file as it describes the necessary information about the class.

| Type | Name | Description |
| :---: | --- | --- |
| **[ConstantPool](#constant-pool)** | **constantPool** | The constant pool of the file. |
| **[EClassFlags](#eclassflags)** | **classFlags** | Flags describing this class. |
| **UI2** | **flags** | A **[CLASS](#class-entry)* entry in the constant pool which describes this class. |
| **UI2** | **superCount** | The number of super classes. |
| **UI2\[superCount]** | **supers** | The supers of this class. |
| **UI2** | **fieldCount** | The number of fields in this class. |
| **[Field](#field)\[fieldCount]** | **fields** | The fields of this class. |
| **UI2** | **methodCount** | The number of methods in this class. |
| **[Method](#method)\[methodCount]** | **methods** | The methods of this class. |
| **UI2** | **attributeCount** | The number of attributes in this class. |
| **[Attribute](#attribute)\[attributeCount]** | **attibutes** | The attributes of this class. |

### **EClassFlags**
Type = **UI2**
| Value | Name | Description |
| :---: | --- | --- |
| **0** | **None** | No flags. |

### **Class id format**
The format of a Class id is a case-sensitive [unix path](https://en.wikipedia.org/wiki/Path_(computing)#Unix_style).

## Constant Pool
The constant pool is a list of constant values to be used when parsing and linking the file.

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **size** | The number of constants in the constant pool pluss 1. |
| **[ConstantPoolEntry](#constant-pool-entry)\[size-1]** | **entries** | The entries in the constant pool. |

## Constant Pool Entry
There are a couple of constant pool entry types, all of which start with the data below.

| Type | Name | Description |
| :---: | --- | --- |
| **UI1** | **tag** | A tag identifier for the constant pool entry. |

### **CLASS** Entry
A Class entry describes a class.  
**tag** = 1

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **nameEntry** | A **[UTF8](#utf8-entry)** entry in this constant pool which describes the name of this class entry. |

### **UTF8** Entry
A UTF8 entry describes a UTF-8 encoded string.  
**tag** = 2

| Type | Name | Description |
| :---: | --- | --- |
| **UI4** | **length** | The length of this UTF-8 encoded string. |
| **UI1\[length]** | **string** | The actual string. |

## Field
The field struct stores necessary information about a field in the class.

| Type | Name | Description |
| :---: | --- | --- |
| **[EFieldFlags](#efieldflags)** | **flags** | Flags describing this field. |
| **UI2** | **idEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes this field's id. |
| **UI2** | **attributeCount** | The number of attributes in this field. |
| **[Attribute](#attribute)\[attributeCount]** | **attibutes** | The attributes of this field. |

The attributes of this field can (All others are ignored) be one of the following.
1. **[ConstantValue Attribute](#constantvalue-attribute)**

### **Field id format**
The format of a Field id is:
```
FieldId:
  FieldName ; FieldType

FieldType:
  PrimitiveType
  ClassType

PrimitiveType:
  (one of)
  I1, I2, I4, I8, UI1, UI2, UI4, UI8, C1, C2, C4, F4, F8

ClassType:
  L ClassId ;
```
FieldName represents a string with at least one character and must not contain any of the ASCII characters `.` `;` `[` `/`.

### **EFieldFlags**
Type = **UI2**
| Value | Name | Description |
| :---: | --- | --- |
| **0** | **None** | No flags. |
| **1** | **Static** | The field is static. |

## Method
The method struct stores necessary information about a method in the class.

| Type | Name | Description |
| :---: | --- | --- |
| **[EMethodFlags](#emethodflags)** | **flags** | Flags describing this field. |
| **UI2** | **idEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes this method's id. |
| **UI2** | **attributeCount** | The number of attributes in this method. |
| **[Attribute](#attribute)\[attributeCount]** | **attibutes** | The attributes of this method. |

The attributes of this method can (All others are ignored) be one of the following.
1. **[Code Attribute](#code-attribute)**

### **Method id format**
The format of a Method id is:
```
MethodId:
  MethodName ; ( ) ReturnType
  MethodName ; ( FieldType ) ReturnType
  MethodName ; ( FieldType {, FieldType} ) ReturnType

FieldType:
  PrimitiveType
  ClassType

ReturnType:
  FieldType
  VoidType

PrimitiveType:
  (one of)
  I1, I2, I4, I8, UI1, UI2, UI4, UI8, C1, C2, C4, F4, F8

ClassType:
  L ClassId ;

VoidType:
  V
```
MethodName represents a string with at least one character and must not contain any of the ASCII characters `.` `;` `[` `/`.

### **EMethodFlags**
Type = **UI2**
| Value | Name | Description |
| :---: | --- | --- |
| **0** | **None** | No flags. |
| **1** | **Static** | The field is static. |

## Attribute
The attribute struct stores ncessary information about an attribute in the class, field or method.

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **nameEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes this attribute's name. |
| **UI4** | **attributeLength** | The length of this attribute. |
| **UI1\[attributeLength]** | **data** | The data of this attribute. |

### **ConstantValue** Attribute
**nameEntry** = "ConstantValue"  
**attributeLength** = 2  
**data**:

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **constantEntry** | An entry in the constant pool which stores the constant value. |

### **Code** Attribute
**nameEntry** = "Code"  
**data**:

| Type | Name | Description |
| :---: | --- | --- |
| **UI4** | **codeLength** | The length of the code in this code attribute. |
| **UI1\[codeLength]** | **code** | The code in this code attribute. |
| **UI2** | **attributeCount** | The number of attributes in this code attribute. |
| **[Attribute](#attribute)\[attributeCount]** | **attributes** | The attributes of this code attribute. |

The attributes of this code attribute can (All others are ignored) be one of the following.
1. **[MethodRef Attribute](#methodref-attribute)**
2. **[FieldRef Attribute](#fieldref-attribute)**

### **MethodRef** Attribute
**nameEntry** = "MethodRef"  
**attributeLength** = 4  
**data**:

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **classEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes the id of the class this method reference goes to. |
| **UI2** | **methodEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes the id of the method this method reference goes to. |


### **FieldRef** Attribute
**nameEntry** = "FieldRef"  
**attributeLength** = 4  
**data**:

| Type | Name | Description |
| :---: | --- | --- |
| **UI2** | **classEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes the id of the class this field reference goes to. |
| **UI2** | **fieldEntry** | A **[UTF8](#utf8-entry)** entry in the constant pool which describes the id of the method this field reference goes to. |
