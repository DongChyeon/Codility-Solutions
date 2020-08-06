#include <algorithm>

int solution(vector<int>& A) {
	vector<int> lower;
	vector<long long> upper;
	int cnt = 0;
	int j = 0;

	for (int i = 0; i < A.size(); i++) {
		lower.push_back(i - A[i]);
		upper.push_back((long long)i + A[i]);
	}

	sort(lower.begin(), lower.end());
	sort(upper.begin(), upper.end());

	for (int i = 0; i < A.size(); i++) {
		while (j < A.size() && upper[i] >= lower[j]) {
			cnt += j;
			cnt -= i;	// 이전 uppper와 겹치지 않기 위해서 빼준다
			j++;
		}
	}

	if (cnt > 10000000) return -1;
	return cnt;
}

/*
이해가 잘 안되서 설명 추가
{ 1, 5, 2, 1, 4, 0 }을 예시로 시작점 기준으로 가장 왼쪽의 원인 시작점, 끝점이 (-4, 6) 을 예로 들어보자. 이 원의 끝점인 6을 기준으로 그 앞쪽에 위치한 원의 시작점은 [-4, -1, 0, 0, 2, 5] 총 6개이고 그중 -4 는 자기 자신의 시작점이므로 카운트에서 제외해야 한다. 따라서 총 5개.
그 다음의 원인 시작점, 끝점이 (-1, 1) 인 원을 보자. 이 원의 끝점 1의 앞쪽에 위치한 시작점은 [-4, -1, 0, 0] 이다. 마찬가지로 -1은 자기 자신이므로 제외한다. 그리고 -4도 제외해야 한다. 이유는 (-4, 6) 과 (-1, 1) 쌍의 원은 이미 (-4, 6) 의 원을 기준으로 계산할때 카운트되었기 때문이다.
다음 계산할 원은 0으로 시작하는 원인데 (0, 4), (0, 8) 두 개가 있다. 아무거나 먼저 선택해도 무방하다. (0, 4) 를 먼저 계산해보자. 4를 기준으로 앞쪽의 시작점은 [-4, -1, 0, 0, 2] 5개다. 0하나는 자기 자신이니 제외. -4 와 -1 은 앞 단계들에서 이미 계산되었기 때문에 제외.
그 다음 (0, 8) 의 원. 8의 앞쪽 시작점들은 [-4, -1, 0, 0, 2, 5]. 0 하나는 자기자신이므로 제외. [-4, -1, 0] 세 개는 앞에서 이미 계산된 것들이어서 제외.
여기서 법칙을 세울수 있다. 시작점 기준으로 정렬을 시킨후 정렬된 원을 하나 하나 계산한다. 하나의 원을 계산할때, 자신의 끝점보다 앞쪽에 위치한 시작점들의 갯수를 구한 다음 여기서 자기 자신과, 이미 계산한 시작점들의 갯수를 빼주면 된다. 이들의 총합이 답이 된다.
*/