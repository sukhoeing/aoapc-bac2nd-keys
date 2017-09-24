// LA4369 - I Speak Whales
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

typedef long long LL;

LL solve(LL N, LL R, LL S, LL E) {
	if (N == 0) {
		// assert(!R && !S && !E);
		return 1;
	}

	LL ans = 0, w = 1LL<<(N-1);

	if (R < w) {
		if (w <= S) 
			ans += solve(N - 1, R, S - w, E - w);
		else {
			ans += solve(N - 1, R, S, min(w - 1, E));
			if (E >= w)
				ans += solve(N - 1, R, 0, E - w);
		}
	}
	else {
		if (w <= S)
			ans -= solve(N - 1, R - w, S - w, E - w);
		else {
			ans += solve(N - 1, R - w, S, min(w - 1, E));
			if (E >= w) ans -= solve(N - 1, R - w, 0, E - w);
		}
	}
	return ans;
}

int main(){
	LL N, R, S, E;
	while (cin>>N>>R>>S>>E && N >= 0) cout << solve(N, R, S, E) << endl;
	return 0;
}
// 1542655 4369 I Speak Whales Accepted C++ 0.079  2014-09-12 13:27:01 