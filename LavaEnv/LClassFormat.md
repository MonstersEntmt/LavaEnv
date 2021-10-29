# LClass V1 file format specification
This markdown file describes the format of an `.lclass` file.<br>
The file format of `.lclass` has a striking ressemblence of Java's `.class` file format.

## Header
The header is very tiny as it only describes the file as being an lclass file and what version of the file format it is.<br>
As this allows breaking the file format afterwards to allow better file formats in the future.

UI4 **magicNumber**: The magic number of the lclass file format, it's value should always equal the string "**HOTL**" for Hot Lava<br>
UI2 **formatVersion**: The version of the lclass file format, should be the value 1 for the version described here.

## Constant Pool
The constant pool is a list of constant values to be used when parsing and linking the file.

UI2 **size**: The number of constants in the constant pool + 1.<br>
ConstantPoolEntry[**size**-1] **entries**: The entries in the constant pool.

## Constant Pool Entry
There are a couple of constant pool entry types, all of which have the data below.<br>
The list of types are:
- **CLASS**: 1
- **UTF8**: 2

UI1 **tag**: The tag of the constant pool entry

For **CLASS**, **tag** has to be 1 and has the extra data below.

UI2 **nameIndex**: An index to a **UTF8** constant pool entry used to describe the name of the class.

For **UTF8**, **tag** has to be 2 and has the extra data below.

UI4 **length**: The length of the UTF8 encoded string.<br>
UI1[**length**] **string**: The actual string.

## Class Information
The class information stores necessary information about the class.

UI2 **classFlags**: Flags describing this class.<br>
UI2 **classEntry**: **CLASS** entry in the constant pool of this class.<br>
UI2 **superCount**: The number of super classes.<br>
UI2[**superCount**] **supers**: The supers of this class.<br>
UI2 **fieldCount**: The number of fields in this class.<br>
Field[**fieldCount**] **fields**: The fields of this class.<br>
UI2 **methodCount**: The number of methods in this class.<br>
Method[**methodCount**]: The methods of this class.<br>
UI2 **attributeCount**: The number of attributes in this class.<br>
Attribute[**attributeCount**] **attributes**: The attributes of this class.

## Field

UI2 **flags**: Flags describing this field.<br>
UI2 **idEntry**: **UTF8** entry in the constant pool describing the id of this field.<br>
UI2 **attributeCount**: The number of attributes in this field.<br>
Attribute[**attributeCount**] **attributes**: The attributes of this field.

## Method

UI2 **flags**: Flags describing this field.<br>
UI2 **idEntry**: **UTF8** entry in the constant pool describing the id of this method.<br>
UI2 **attributeCount**: The number of attributes in this method.<br>
Attribute[**attributeCount**] **attributes**: The attributes of this method.

## Attribute

UI2 **nameEntry**: **UTF8** entry in the constant pool describing the name of this attribute.<br>
UI4 **attributeLength**: The length of this attribute.<br>
UI1[**attributeLength**] **data**: The data of this attribute.
