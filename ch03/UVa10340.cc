// UVa10340 All in All
// 陈锋
#include <cstdio>
#include <cstring>
const int LEN = 100024;
char s[LEN], t[LEN];
int main() {
	while (scanf("%s%s", s, t) == 2) {
		int sLen = strlen(s), tLen = strlen(t);
		bool ok = true;
		for (int i = 0, j = 0; i < sLen; i++, j++) {
			while (j < tLen && t[j] != s[i]) j++;
			if (j == tLen) { ok = false; break; }
		}
		printf("%s\n", ok ? "Yes" : "No" );
	}
	return 0;
}