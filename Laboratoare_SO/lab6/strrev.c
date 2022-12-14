#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* reverse(void* s) {
	char* str = (char*) s;
	char* ans = malloc(sizeof(char) * (strlen(str)+1));
	strcpy(ans, str);

	int i = 0, j = strlen(ans) - 1;
	while (i < j) {
		char c = ans[i];
		ans[i++] = ans[j];
		ans[j--] = c;
	}
	
	return ans;
}

int main(int argc, char** argv) {
	char* s = argv[1];
	pthread_t thr;
	pthread_create(&thr, NULL, reverse, s);

	void* result;
	pthread_join(thr, &result);
	
	printf("%s\n", (char*) result);
	free(result);
	return 0;
}