/*
 * File:   Huffman.cpp
 * Author: Michael Horn
 *
 * Created on 27. November 2015, 09:45
 */

#include "Huffman.h"

Huffman::Huffman(bool time) {
    timeMeasurement = time;

}

Huffman::~Huffman() {
}

// Zählt das Auftreten der Symbole und speichert sie in SymbolsCount
void Huffman::getSymbolsCount(const std::deque<char> &input, std::unordered_map<char, unsigned long> &symbolsCount){

    for (unsigned long i = 0; i < input.size(); i++) {
        auto it = symbolsCount.find(input[i]);
        if (it != symbolsCount.end()) {
            (it->second)++;
        } else {
            symbolsCount[input[i]] = 1;
        }
    }
    return;
}

//Baut den HuffmanTree anhand des Auftretens von Symbolen auf
Node* Huffman::buildTree(std::unordered_map<char, unsigned long> &symbolsCount) {

    //Sortiere die Symbole anhand der Anzahl von min zu max
    //Und erzeuge für jedes Symbol einen Knoten
    auto sizeOfSymbolsCount = symbolsCount.size();
    std::deque<Node*> minToMaxNodes;
    for (auto i = 0; i < sizeOfSymbolsCount; i++) {
        char tempSymbol;
        unsigned  long maxOccurrence = 0;
        for (auto it = symbolsCount.begin(); it != symbolsCount.end(); ++it) {
            if (maxOccurrence < it->second) {
                tempSymbol = it->first;
                maxOccurrence = it->second;
            }
        }
        Node* initNode = new Node(tempSymbol,maxOccurrence);
        minToMaxNodes.push_front(initNode);
        symbolsCount.erase(tempSymbol);
    }
    symbolsCount.clear();

    std::deque<Node*> huffmanTree;
    //Fuege als initialisierung einen Knoten in den Huffman-Tree ein
   if(minToMaxNodes.size() > 1){
        Node* left = minToMaxNodes.front();
        minToMaxNodes.pop_front();
        Node* right = minToMaxNodes.front();
        minToMaxNodes.pop_front();

        Node* root = new Node('\0',left->getWeight()+right->getWeight());
        root->setChildNodes(left,right);
        huffmanTree.push_back(root);
    }

    //Erzeuge den Huffman-Tree
    while(minToMaxNodes.size() > 1){
        Node* root = new Node('\0', 0);
        Node* left = NULL;
        Node* right = NULL;

        if(minToMaxNodes[1]->getWeight() <= huffmanTree.front()->getWeight()){
            left = minToMaxNodes.front();
            minToMaxNodes.pop_front();
            right = minToMaxNodes.front();
            minToMaxNodes.pop_front();

        }else if(minToMaxNodes.front()->getWeight() <= huffmanTree.front()->getWeight()){
            left = minToMaxNodes.front();
            minToMaxNodes.pop_front();
            right = huffmanTree.front();
            huffmanTree.pop_front();

        }else if(huffmanTree.size() >1) {
            if(minToMaxNodes[1]->getWeight() < huffmanTree[1]->getWeight()){
                left = huffmanTree.front();
                huffmanTree.pop_front();
                right = minToMaxNodes.front();
                minToMaxNodes.pop_front();
            }else {
                left = huffmanTree.front();
                huffmanTree.pop_front();
                right = huffmanTree.front();
                huffmanTree.pop_front();
            }
        }else{
            left = huffmanTree.front();
            huffmanTree.pop_front();
            right = minToMaxNodes.front();
            minToMaxNodes.pop_front();
        }

        root->setWeight(left->getWeight() + right->getWeight());
        root->setChildNodes(left,right);
        huffmanTree.push_back(root);
    }

    //Sollten noch einzelne Knoten existieren, so fuege diese noch in den Baum ein
    while(huffmanTree.size() > 1 || !minToMaxNodes.empty()) {

        Node *root = new Node('\0', 0);
        Node *left = NULL;
        Node *right = NULL;

        if (!minToMaxNodes.empty()) {
            //Wenn der Huffman-Tree leer ist, aber ein Symbol erzeugt, so muss dies entsprechend behandelt werden!
            if(huffmanTree.empty()){
                huffmanTree.push_back(minToMaxNodes.front());
                minToMaxNodes.pop_front();
                break;
            }
            else if (minToMaxNodes.front()->getWeight() <= huffmanTree.front()->getWeight()) {
                left = minToMaxNodes.front();
                minToMaxNodes.pop_front();
                right = huffmanTree.front();
                huffmanTree.pop_front();
            }else{
                left = huffmanTree.front();
                huffmanTree.pop_front();
                right = huffmanTree.front();
                huffmanTree.pop_front();
            }
        }else{
            left = huffmanTree.front();
            huffmanTree.pop_front();
            right = huffmanTree.front();
            huffmanTree.pop_front();
        }

        root->setWeight(left->getWeight() + right->getWeight());
        root->setChildNodes(left, right);
        huffmanTree.push_back(root);

    }

    assert(minToMaxNodes.size()==0);
    assert(huffmanTree.size()==1);

    minToMaxNodes.clear();
    Node* tree = huffmanTree.front();
    huffmanTree.clear();
    return tree;
}

//Rekursion baut den CodeTree für den Huffman-Tree auf und speichert das Ergebnis in einer HashMap (schnellerer zugriff)
void Huffman::codeGenerator(Node* tree,std::unordered_map<char,std::deque<bool>>& codedSymbol){

    static std::deque<bool> code;

    if (tree->getLeftNode() != NULL)
    {
        code.push_back(false);
        codeGenerator(tree->getLeftNode(),codedSymbol);
        code.pop_back();
    }
    if (tree->getRightNode() != NULL)
    {
        code.push_back(true);
        codeGenerator(tree->getRightNode(),codedSymbol);
        code.pop_back();
    }
    if(!tree->getLeftNode() && !tree->getRightNode())
    {
        //spezialfall: Nur ein Symbol existiert!
        if(code.empty()){
           code.push_back(true);
        }

        codedSymbol[tree->getSymbol()] = code;
    }
}

//TODO Diese funktion wird später durch LZ77 aufgerufen
void Huffman::compressText() {
    /*for (auto it= codedSymbols.begin(); it != codedSymbols.end(); ++it) {
        std::cout << it->first << " ";
        std::copy(it->second.begin(), it->second.end(), std::ostream_iterator<bool>(std::cout));
        std::cout << std::endl;
    }*/
}

//Führt die Huffman Kodierung für eine Datei aus
double Huffman::compressFile(const std::string& inFileName, const std::string& outFileName) {

    const unsigned short bufferLength= 32*1024; //Buffergöße um aus Datei zu lesen

    //kann input File geöffnet werden?
    std::ifstream inputFile(inFileName, std::ifstream::binary);
    if (!inputFile.good()) {
        inputFile.close();
        return -1;
    }

    std::ofstream outFile(outFileName, std::ofstream::binary | std::ofstream::trunc);
    //Enthält auftretn von Zeichen, um dynamisch den Baum zu codieren
    std::unordered_map<char, unsigned long> symbolsCount;

    double time1 = 0.0;
    double tStart = 0.0;
    if(timeMeasurement) {
        tStart = clock();
    }

    while (!inputFile.eof()) {
        char *convPreBuffer = new char[bufferLength];
        auto bytesReaded = inputFile.readsome(convPreBuffer, bufferLength);
        std::deque<char> buffer; //Buffer um aus Datei zu lesen

        //TODO vielleicht parallelisierbar
        for (auto i = 0; i < bytesReaded; i++) {
            buffer.push_back(convPreBuffer[i]);
        }
        delete[] convPreBuffer;

        //Zähle jedes Zeichen in der Datei
        getSymbolsCount(buffer,symbolsCount);

        inputFile.peek();
        buffer.clear();
    }

    std::unordered_map<char,std::deque<bool>> codedSymbols; //Hält codierte Zeichen in HashMap

    //baut den Huffmantree auf mit Hilfe der vorkommen von Symbolen
    Node* tree = buildTree(symbolsCount);
    //baut den Codierungsbaum auf
    codeGenerator(tree,codedSymbols);
    delete tree;

    //Setze Datei wieder auf Anfang
    inputFile.clear();
    inputFile.seekg(0,std::ios::beg);

    //Codiere jetzt die Datei
    while (!inputFile.eof()) {
        char* convPreBuffer = new char[bufferLength];
        auto bytesReaded = inputFile.readsome(convPreBuffer, bufferLength);
        //char zu char* geändert, da als pointer performanter...
        std::deque<char*> buffer; //Buffer um aus Datei zu lesen
        for (auto i = 0; i < bytesReaded; i++) {
            buffer.push_back(&convPreBuffer[i]);
        }

        for (auto it= buffer.begin(); it != buffer.end(); ++it) {
            //Finde das gelesene Zeichen und die entsprechende Codierung und speicher sie ab
            auto iti = codedSymbols.find(**it);
            //TODO Derzeit Byteweises speichern des Codes->Später speichern als Bits
            if (!timeMeasurement){
                std::copy(iti->second.begin(), iti->second.end(), std::ostream_iterator<bool>(outFile));
            }
        }

        delete[] convPreBuffer;
        inputFile.peek();
        buffer.clear();
    }
    inputFile.close();
    outFile.close();
    codedSymbols.clear();
    symbolsCount.clear();

    if(timeMeasurement) {
        time1 += clock() - tStart;
        time1 = time1 / CLOCKS_PER_SEC;
    }
    return time1;
}
