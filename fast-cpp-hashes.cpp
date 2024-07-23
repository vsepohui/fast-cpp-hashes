#include <stdio.h>
#include <string.h>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>



template <class T>
class Hash {
	public: 
		Hash() {
		};
		
		T value;
		int cnt = 0;

		std::map <char,Hash<T>*> node;
		
		
		operator bool() {
			return this->node.size() != 0;
		}
		
		Hash <T>* step (char c) {	
		
			
		//	if (this->node[c].node == NULL) {
			//	return NULL;
			//}
			if(this->node.find(c) != this->node.end()) {

				return this->node[c];
			}
			
			return NULL;
		}
		

		T* get (char* key) {
			//printf ("GETTING %s\n", key);
			Hash <T>* index = this;
			int len = strlen(key);
				
			for (int i = 0; i < len; i++) {
				
				//printf("%c\n", key[i]);
				
				if (index->step(key[i]) != NULL) {
					index = index->step(key[i]);
				} else {
					return NULL;
				}
			}
			return &(index->value);
		}
		
		T set (char* key, T val) {
		//	printf ("SETTING %s\n", key);
			Hash <T>* index = this;
			int len = strlen(key);
			for (int i = 0; i < len; i++) {
				if (index->node[key[i]] == NULL)
					index->node[key[i]] = new Hash <T>;
				index = index->node[key[i]];
				index->cnt ++;
			}
			index->value = val;
			return val;
		}
		
		T* deleting (char* key) { 
			
		//	printf ("DELETING %s\n", key);
			Hash <T>* index = this;
			Hash <T>**ref;
			T * result = NULL;
			int len = strlen(key);
			ref = (Hash <T>**)malloc(sizeof(Hash*) * len);

			for (int i = 0; i < len; i++) {
				if (key[i]) {
					index = index->step(key[i]);
					if (!index) break;
					
					index->cnt --;
								
					ref [i] = index;
				} else {
					break;
				}
			}
			
			
			
			
			if (!index) return NULL;
			
			
			
			
			result = &(index->value);
			for (int i = len - 1; i >= 0; i--) {
				if (ref[i]->cnt == 0) {
					if (ref[i]) {
						delete (ref[i]);
					} else {
						break;
					}
				} else {
					break;
				}
			}
			
			
			if (ref) free (ref);
			return result;
		}
		
		T renaming(char* key, char *key2) {
			
//			printf ("RENAMING %s TO %s\n", key, key2);
		
			T * val2 = this->get(key);
			T * val3;
			memcpy(val3,val2, sizeof(val2));
			this->deleting(key);

			return this->set(key2, *val3);
		}
};

int main () {
	Hash <int> *h = new Hash<int>;
	
	
	
	printf ("%d\n", h->set("asd", 123));
	printf ("%d\n", *(h->get("asd")));
	printf ("%d\n", h->set("asd2", 1234));
	printf ("%d\n", h->set("asd3", 12356));
	
	int *v = h->deleting("asd54");
	printf ("%d\n", v ? *v : 0);	
	printf ("%d\n", *(h->get("asd")));	
	
	printf ("%d\n", *(h->get("asd")));
	
	v = h->deleting("asd");
	printf ("%d\n", v ? *v: 0 );
	
	printf ("%d\n", h->renaming("asd3", "kush"));
	
	v = h->get("kush");
	printf ("%d\n", v != NULL ? *v : 0);
	
	

	Hash <std::string> *s = new Hash<std::string>;
	
	
	
	std::string str = "Hello World!";
	std::cout << s->set("key", str) << std::endl;
	std::cout << *(s->get("key")) << std::endl;

}
