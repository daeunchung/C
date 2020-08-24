#pragma warning (disable:4996)

#include "library.h"
#include "string_tools.h"
#include <Windows.h>
#include <stdlib.h>

#define NUM_CHARS 256	// 2 ^ 8 = 256
#define SIZE_INDEX_TABLE 100
#define BUFFER_LENGTH 200


Artist * artist_directory[NUM_CHARS];
sNode * index_directory[SIZE_INDEX_TABLE];
int num_index = 0;

Song * create_song_instance(Artist * ptr_artist, char * title, char * path);
Artist * create_artist_instance(char * name);
void insert_node(Artist * ptr_artist, sNode * ptr_snode);
void print_artist(Artist * p);
Artist * find_artist(char * name);
void print_song(Song * ptr_song);
sNode * find_snode(Artist * ptr_artist, char * title);
void insert_to_index_directory(Song * ptr_song);
void save_artist(Artist * p, FILE * fp);
void save_song(Song * ptr_song, FILE * fp);
void destory_song(Song * ptr_song);
void remove_snode(Artist * ptr_artist, sNode * ptr_snode);




void initialize() {
	for (int i = 0; i < NUM_CHARS; i++) {
		artist_directory[i] = NULL;
	}
	for (int i = 0; i < SIZE_INDEX_TABLE; i++) {
		index_directory[i] = NULL;
	}
}

void load(FILE *fp) {
	char buffer[BUFFER_LENGTH];
	char * name, *title, *path;

	while (1) {			// infinite loop
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)	// get a line
			break;

		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0)
			name = NULL;
		else
			name = strdup(name);

		title = strtok(NULL, "#");
		if (strcmp(name, " ") == 0)
			title = NULL;
		else
			title = strdup(title);

		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0)
			path = NULL;
		else
			path = strdup(path);

		//printf("%s %s %s \n", name, title, path);
		add_song(name, title, path);
	}

}


void search_song(char* artist, char * title) {

	Artist * ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}

	sNode * ptr_snode = find_snode(ptr_artist, title);
	if (ptr_snode != NULL) {
		printf("Found:\n");
		print_song(ptr_snode->song);
	}
	else {
		printf("No such artist exists.\n");
		return;
	}
}


// �ٸ� ������ �� �Լ��� ����� �ֱ� ���ؼ� �������Ѽ� ��������
sNode * find_snode(Artist * ptr_artist, char * title) {
	sNode * ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
		ptr_snode = ptr_snode;

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) {
		//printf("Found:\n");
		//print_song(ptr_snode->song);
		return ptr_snode;
	}
	else {
		//printf("No such artist exists.\n");
		//return;
		return NULL;
	}
}

void search_song(char* artist) {
	Artist * ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}
	printf("Found\n");
	print_artist(ptr_artist);
}

// ��ü�����Լ�
Artist * create_artist_instance(char * name) {
	Artist * ptr_artist = (Artist *)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;
	return ptr_artist;
}

Artist * add_artist(char * name) {
	Artist * ptr_artist = create_artist_instance(name);

	Artist * p = artist_directory[(unsigned char)name[0]];	// first node
	Artist * q = NULL;

	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL)		// unique node
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	else if (q == NULL) {			// add at the front
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else {							// add_after(q);
		ptr_artist->next = p;
		q->next = ptr_artist;
	}

	return ptr_artist;
}

Song * create_song_instance(Artist * ptr_artist, char * title, char * path) {
	Song * ptr_song = (song *)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;
	 
	return ptr_song;

}

void add_song(char * artist, char * title, char * path) {

	// find if the artist already exists
	// return NULL if not

	Artist * ptr_artist = find_artist(artist);	
	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist);
	}

	// add the song to the artist pointed by ptr_artist
	Song * ptr_song = create_song_instance(ptr_artist, title, path);
	sNode * ptr_snode = (sNode *)malloc(sizeof(sNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;


	// insert node
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

void insert_to_index_directory(Song * ptr_song) {
	sNode * ptr_snode = (sNode *)malloc(sizeof(sNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	//ptr_snode->prev = NULL;	// unused

	int index = ptr_song->index % SIZE_INDEX_TABLE;

	// insert the snode into the single linked list at index_table[index]
	sNode * p = index_directory[index];
	sNode * q = NULL;	// ordered single linked list �� �����ϱ� ���ؼ��� ������ �ϳ� �� �ʿ���
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {
		q = p;
		p = p->next;
	}

	if (q == NULL) {		// add_first
		ptr_snode->next = p;
		index_directory[index] = ptr_snode;
	}
	else {					// add_after q
		ptr_snode->next = p;
		q->next = ptr_snode;
	}
}

void insert_node(Artist * ptr_artist, sNode * ptr_snode) {
	sNode * p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0)
		p = p->next;

	if (ptr_artist->head == NULL) {		// empty
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) {	// at the front
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;

	}
	else if (p == NULL) {				// at the end
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else {								// before p  
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	} 
}
 

Artist * find_artist(char * name) {

	// first artist with initial name[0]
	// 0 ~ 256  ���̰����� ���ֱ� ���ؼ� unsigned char �� ! 
	Artist * p = artist_directory[(unsigned char)name[0]];		
	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;


	//if (p == NULL)
	//	return NULL;
	//else
	//	return p;

	/* name[0] : 00000000 ~ 11111111 */
	/* 1101111 -> 111111111111111111111001111 �����δ� �̷��� �ż� ����ó�� �ȴ� => unsigned �� �����ʿ� */

}

void status() {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist * p = artist_directory[i];
		while (p != NULL) {
			print_artist(p);
			p = p->next;
		}
	}
}

void print_artist(Artist * p) {
	printf("%s\n", p->name);
	sNode * ptr_sNode = p->head;
	while (ptr_sNode != NULL) {
		print_song(ptr_sNode->song);
		ptr_sNode = ptr_sNode->next;
	}
}

void print_song(Song * ptr_song) {
	printf("	%d : %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);

}

sNode * find_song(int index) {
	sNode * ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void play(int index) {
	sNode * ptr_snode = find_song(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
	}

	printf("Found the song : %s", ptr_snode->song->title);

	// �� ������ �÷��̾�� ��� �ϸ� ���� �����ϰ� ������ �÷��� �ϴ°�
	// ������ ����Ŭ���ؼ� �����ϴ� ��
	ShellExecute(GetDesktopWindow(), "open", ptr_snode->song->path, NULL, NULL, SW_SHOW);
}

void save(FILE * fp) {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist * p = artist_directory[i];
		while (p != NULL) {
			save_artist(p, fp);
			p = p->next;
		}
	}
}

void save_artist(Artist * p, FILE * fp) {
	sNode * ptr_sNode = p->head;
	while (ptr_sNode != NULL) {
		save_song(ptr_sNode->song, fp);
		ptr_sNode = ptr_sNode->next;
	}
}

void save_song(Song * ptr_song, FILE * fp) {

	if (ptr_song->artist != NULL)
		fprintf(fp, "%s#", ptr_song->artist->name);
	else
		fprintf(fp, " #");

	if (ptr_song->title != NULL)
		fprintf(fp, "%s#", ptr_song->title);
	else
		fprintf(fp, " #");

	if (ptr_song->path != NULL)
		fprintf(fp, "%s#\n", ptr_song->path);
	else
		fprintf(fp, " #\n");
		
}

void remove(int index) {
	// find the song

	sNode * q = NULL;										// previous to p
	sNode * p = index_directory[index % SIZE_INDEX_TABLE];	// head node
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}
	if (p == NULL) {		// either empty list or not exist
		printf("No such song exists.\n");
		return;
	}
	Song * ptr_song = p->song;
	if (q == NULL) {		// remove first
		index_directory[index % SIZE_INDEX_TABLE] = p->next;
	}
	else {					// remove after q
		q->next = p->next;	// q->next = q->next->next; �� �����Ҹ�
	}
	free(p);



	Artist * ptr_artist = ptr_song->artist;
	// find the snode in the double linked list of ptr_artist

	sNode * ptr_snode = find_snode(ptr_artist, ptr_song->title);
	if (ptr_snode == NULL) {
		printf("Not found snode - something wrong.\n");
		return;
	}

	remove_snode(ptr_artist, ptr_snode);
	destory_song(ptr_song);

}

void destory_song(Song * ptr_song) {
	if (ptr_song->title != NULL)
		free(ptr_song->title);
	if (ptr_song->path != NULL)
		free(ptr_song->path);
	free(ptr_song);
}

void remove_snode(Artist * ptr_artist, sNode * ptr_snode) {
	sNode * first = ptr_artist->head;
	sNode * last = ptr_artist->tail;

	if (first == ptr_snode && last == ptr_snode) {	// unique node

	}
	else if (first == ptr_snode) {					// remove first

	}
	else if (last == ptr_snode) {					// remove last

	}
	else {											// in the middle

	}
	free(ptr_snode); 
}