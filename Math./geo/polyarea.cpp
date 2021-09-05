// https://en.wikipedia.org/wiki/Shoelace_formula#Definition


int getarea(const vector<pair<int,int>> pt) {
	int area = 0;
  int len = (int)pt.size();
	for(int i = 0 ; i < len ; ++i) {
		int j = (i + 1) % pt.size();
		area += pt[i].first * pt[j].second - pt[j].first * pt[i].second;
	}
	return area;
}
