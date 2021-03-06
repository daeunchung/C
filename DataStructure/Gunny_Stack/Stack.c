#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// 舘析 尻衣軒什闘稽 什澱 坪漁

typedef struct sNode
{
	char* data;
	struct sNode* next;

}Node;

typedef struct listStack
{
	Node* peek;
	int size;
}listStack;

// Stack 拭 慎肇 隔奄 ( 五乞軒 隔嬢爽奄, 拝雁馬奄)
void createStack(listStack** Stack) {

	(*Stack) = (listStack*)malloc(sizeof(listStack));

	(*Stack)->peek = NULL;
	(*Stack)->size = 0;

}


// Node 拭 慎肇 隔奄 (五乞軒 隔嬢爽奄)
Node* createNode(char* newChar) {

	//1. 葛球 持失板 五乞軒 拝雁
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = (char*)malloc(strlen((newChar) + 1));

	// data拭 庚切伸聖 copy
	strcpy(newNode->data, newChar);
	newNode->next = NULL;
}

// Node 五乞軒 宋戚奄
void deleteNode(Node* removeNode) {

	free(removeNode->data);
	free(removeNode);
	// 鎧遂 走酔壱 葛球 走酔壱 却 陥 背操醤敗
}

Node* Pop(listStack* Stack) {	// 鎧亜 脊径廃(戚 什澱) 掻拭 亜舌 原走厳 叶(葛球) 襖鎧辞 鋼発背操

	Node* tempNode;
	// when stack is empty
	if (Stack->size == 0) {
		printf("hey!!! stack is empty\n");
		tempNode = NULL;
	}
	// when stack is not empty
	else {
		tempNode = Stack->peek;

		// daeun 坪球  // 葛球拭 peek聖 隔嬢爽汗劃(X),  (号狽戚 戚係惟 掻推杯艦陥_)
		//Stack->peek->next = Stack->peek;	

		//舛岩坪球澗 戚暗 (置雌舘 葛球研 亜軒徹澗peek 聖 陥製 葛球稽 戚疑獣轍陥.)  peek拭 葛球研 隔嬢爽汗劃(O)
		Stack->peek = Stack->peek->next;

		Stack->size--;


	}
	return tempNode;

	//free(tempNode);		// deleteStack敗呪拭辞 背掃艦陥. 
}



// Stack 五乞軒 宋戚奄 ( Stack 紗 Node級 熟 陥 走酔壱 Stack沙昔亀 宋戚澗 章詞切 せせせせ 敗呪)
void deleteStack(listStack* Stack) {

	// Stack 照拭 Node 護鯵 赤澗走 乞牽艦猿 析舘 痕呪稽 幻級嬢辞 閤切
	int count = Stack->size;
	int i;
	Node* tempNode;

	// for庚 宜檎辞 Node 陥 宋戚壱
	for (i = 0; i < count; i++) {
		tempNode = Pop(Stack);	// 置雌是 葛球 詞側梯 災君鎧辞 (Pop敗呪拭 陥製叶聖 歯 peek稽 績誤背 爽澗 奄管猿走 陥 級嬢赤製)
		deleteNode(tempNode);	// 郊~稽 宋食獄顕 せせせ
		//free(tempNode->data);
		//free(tempNode);
	}

	// 原走厳生稽 Stack 亀 宋食爽奄
	free(Stack);
}


// ** 食奄採斗 掻推 敗呪		// (戚 什澱拭, 戚 葛球 隔嬢操)
void Push(listStack* Stack, Node* newNode) {

	// when stack is empty ( peek == NULL || size == 0 )
	if (Stack->size == 0) {
		Stack->peek = newNode;
	}
	// when stack is not empty
	else {
		newNode->next = Stack->peek;
		Stack->peek = newNode;
	}
	Stack->size++;
}






main() {
	int i;
	listStack* Stack;	// Stack 荻汽奄 幻級奄

	createStack(&Stack);	// 慎肇 隔嬢爽奄
	Push(Stack, createNode("a"));
	Push(Stack, createNode("b"));
	Push(Stack, createNode("c"));
	Push(Stack, createNode("d"));

	printf("abcd pushed\n");

	printf("\n -- Current Stack -- [size : %d]\n\n", Stack->size);
	Node* horse = Stack->peek;
	for (i = 0; i < Stack->size; i++) {
		printf("%s\n", horse->data);
		horse = horse->next;
	}

	horse = Pop(Stack);
	horse = Pop(Stack);

	printf("\n -- Current Stack -- [size : %d]\n\n", Stack->size);
	 horse = Stack->peek;
	for (i = 0; i < Stack->size; i++) {
		printf("%s\n", horse->data);
		horse = horse->next;
	}

	deleteStack(Stack);
	printf("\nStack has been completely freed\n");
}


/*
HEAP CORRUPTION DETECTED 神嫌人 背衣号狛

窒坦: https://bozeury.tistory.com/entry/HEAP-CORRUPTION-DETECTED-神嫌人-背衣号狛 
戚 採歳税 拭君澗 sizeof(Test)亜 sizeof(Test*)左陥 滴奄 凶庚拭 析嬢蟹澗 神嫌戚陥.
聡, 叔薦稽 拝雁吉 五乞軒税 滴奄澗 sizeof(Test*)戚走幻
背薦馬形壱 馬澗 五乞軒税 滴奄澗 sizeof(Test)戚奄 凶庚拭 Heap 拭君亜 蟹澗 依戚陥.
益君糠稽 sizeof(Test*)研 sizeof(Test)稽 郊荷檎 背衣 吃 依戚陥.
*/