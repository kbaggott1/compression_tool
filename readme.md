# Compression tool

The goal of this project is to gain more understanding about how file compression works
under the hood as well as sharpening my skills with the C programming language.

I decided to use the Huffman coding data compression algorithm to compress simple text files.

Huffman coding is a popular lossless data compression algorithm that's based on the frequency of occurrence of data items. The idea is to assign shorter codes to more frequently occurring items and longer codes to items that occur less frequently. This results in a more efficient representation of the data, reducing the overall size of the encoded data. Let’s break down the Huffman coding process step-by-step:

## Step 1: Frequency Table Construction 🔢
The first step in Huffman coding is to build a frequency table that records how many times each data item (such as a character in text data) appears. This frequency information is used to build the Huffman tree.

✅ Completed in this repo

## Step 2: Building the Huffman Tree 🌳
A Huffman tree is a binary tree where each leaf node represents a data item (a character, for example), and each internal node represents a combined frequency of its child nodes.

1. **Initial Nodes**: Each item from the frequency table becomes a node, with the frequency as its weight.
2. **Tree Construction**:
   - Place all nodes in a priority queue (or a min-heap) based on their frequencies.
   - Repeatedly remove the two nodes with the lowest frequency from the queue.
   - Create a new internal node with these two nodes as children. The new node's frequency is the sum of the two child nodes' frequencies.
   - Insert the new node back into the priority queue.
   - Repeat until there is only one node left in the queue, which becomes the root of the Huffman tree.

❌ Completed in this repo

> [!NOTE]
> For a really neat visualization of how huffman trees are built from text, check out 
> [this really neat website.](https://cmps-people.ok.ubc.ca/ylucet/DS/Huffman.html)

## Step 3: Generating Codes 🧑‍💻
Once the Huffman tree is constructed, the next step is to generate the codes for each data item.

- Traverse the tree from the root to each leaf node.
- Assign a '0' for every left branch and a '1' for every right branch.
- The sequence of bits collected along the path from the root to a leaf node forms the code for the data item represented by that leaf.

❌ Completed in this repo

## Step 4: Encoding Data 🔒
Using the codes generated from the Huffman tree, replace each data item in the original dataset with its corresponding Huffman code. This encoded data is what gets stored or transmitted, achieving compression.

❌ Completed in this repo

## Step 5: Decoding Data 🔓
To decode the data encoded with Huffman coding, you simply need the encoded data and the Huffman tree.

- Start at the root of the Huffman tree and read the encoded data bit by bit.
- Each '0' means move to the left child of the current node, and each '1' means move to the right child.
- When you reach a leaf node, you've found the corresponding data item. Record that item as part of the decoded output.
- Repeat this process until all bits are consumed.

❌ Completed in this repo

## Practical Considerations 😁
- **Storing the Tree**: For Huffman coding to be practical, the Huffman tree itself (or some equivalent structure like the frequency table) must be stored along with the encoded data. Otherwise, the recipient won't be able to decode the data.
- **Efficiency**: Huffman coding is most efficient when the frequency distribution of the data items is skewed. If all items are equally likely, Huffman coding may not provide much compression.

## Example
Consider the string "this is an example of a huffman tree". The Huffman coding process for this string involves building a frequency table, constructing the Huffman tree, generating codes for each character, encoding the string using these codes, and finally being able to decode the encoded data using the tree.

Huffman coding is widely used in various applications, including file compression formats like ZIP and multimedia codecs. Its main advantage is that it achieves the best possible compression ratio for a given set of data frequencies according to information theory.
