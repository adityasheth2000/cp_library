const long double eps = 1e-12;
const long double infl = 1e20;

template <class T>
inline int sgn(const T & x) {
	return (x > eps) - (x < -eps);
}

template <class T>
struct Point {
 	T x, y;

	Point() : x(0), y(0) {}

	Point(const T & x, const T & y) : x(x), y(y) {}

	long double length() const {
		return sqrtl(x * x + y * y);
	}

	T length2() const {
		return x * x + y * y;
	}

	long double distance(const Point & rhs) const {
		return (rhs - *this).length();
	}

 	T cross(const Point & lhs, const Point & rhs) const {
		return (lhs - *this) * (rhs - *this);
	}

	T dot(const Point & lhs, const Point & rhs) const {
		return (lhs - *this) & (rhs - *this);
	}

	long double distance_to_line(const Point & p, const Point & q) const {
		if (p == q) return distance(p);
		else return fabsl(cross(p, q) / p.distance(q));
	}

	long double distance_to_segment(const Point & p, const Point & q) const {
		if (p == q) return distance(p);
		else if (p.dot(q, *this) < 0) return distance(p);
		else if (q.dot(p, *this) < 0) return distance(q);
		else return distance_to_line(p, q);
	}

	bool on_line(const Point & p, const Point & q) const {
		return sgn(cross(p, q)) == 0;
	}

	bool on_halfline(const Point & p, const Point & q, const bool & inclusive = true) const {
		if (*this == p) return inclusive;
		else return on_line(p, q) && sgn(p.dot(q, *this)) >= 0;
	}

	bool on_segment(const Point & p, const Point & q, const bool & inclusive = true) const {
		if (*this == p || *this == q) return inclusive;
		else return on_line(p, q) && sgn(dot(p, q)) <= 0;
	}

	bool in_triangle(const Point & u, const Point & v, const Point & w, const bool & inclusive = true) const {
		Point p[3] = {u, v, w};
		if (sgn(u.cross(v, w)) < 0) reverse(p, p + 3);
		for (int i = 0; i < 3; i++) {
			if (on_segment(p[i], p[(i + 1) % 3])) return inclusive;
			else if (sgn(cross(p[i], p[(i + 1) % 3])) < 0) return false;
		}
		return true;
	}

	bool in_angle(const Point & o, const Point & p, const Point & q, const bool & inclusive = true) const {
		if (on_halfline(o, p) || on_halfline(o, q)) return inclusive;
		int vs = sgn(o.cross(p, q)), ss = sgn(o.dot(p, q));
		if (vs == 0 && ss > 0) return false;
		int vp = sgn(o.cross(p, *this)), vq = sgn(o.cross(*this, q));
		if (sgn(o.cross(p, q)) >= 0) return vp > 0 && vq > 0;
		else return vp > 0 || vq > 0;
	}

	Point operator + (const Point & rhs) const {// returns a+b(vector addition)
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point & rhs) const {// Returns a-b(vector subtraction)
		return Point(x - rhs.x, y - rhs.y);
	}

	T operator * (const Point & rhs) const { 	// cross product
		return x * rhs.y - y * rhs.x;
	}

	T operator & (const Point & rhs) const { 	// dot product
		return x * rhs.x + y * rhs.y;
	}

	Point operator * (const T & rhs) const {	// multiplication with constant
		return Point(x * rhs, y * rhs);
	}

	Point operator / (const T & rhs) const {	// division with constant
		return Point(x / rhs, y / rhs);
	}

	bool operator == (const Point & rhs) const {// returns true if points are located at the same point.
		return x == rhs.x && y == rhs.y;
	}

	bool operator != (const Point & rhs) const {// returns true if points are not located at same point.
		return x != rhs.x || y != rhs.y;
	}

	inline int quadrant() const {				// returns quadrant defined from 0 to 7 (-1 if origin). Used in operator <
		if (x == 0 && y == 0) return -1;
		else if (x < 0 && y < 0) return 0;
		else if (x == 0 && y < 0) return 1;
		else if (x > 0 && y < 0) return 2;
		else if (x > 0 && y == 0) return 3;
		else if (x > 0 && y > 0) return 4;
		else if (x == 0 && y > 0) return 5;
		else if (x < 0 && y > 0) return 6;
		else return 7;
	}

	bool operator < (const Point & rhs) const {	//used for sorting the points in counter clockwise order.
		int lq = quadrant(), rq = rhs.quadrant();
		if (lq != rq) {
			return lq < rq;
		} else {
			int s = sgn(*this * rhs);
			return s != 0 ? s > 0 : sgn(length2() - rhs.length2()) < 0;
		}
	}
};

template <class T>
inline bool xycmp(const Point<T> & lhs, const Point<T> & rhs) {
	if (lhs.x != rhs.x) return lhs.x < rhs.x;
	else return lhs.y < rhs.y;
}

template <class T>
void convex_hull(vector<Point<T> > p, vector<Point<T> > & ans)  // ans[0] is the leftmost and downmost point, order is ACW.
{
	const int n = p.size();
	Point<T> o = *min_element(p.begin(), p.end(), xycmp<T>);
	for(int i = 0; i < n; i++) p[i] = p[i] - o;
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++) p[i] = o + p[i];
	ans.resize(n);
	int sz = 0;
	ans[sz++] = p[0];
	for(int i = 1; i < n; i++) {
		for(; sz > 1 && sgn(ans[sz - 2].cross(ans[sz - 1], p[i])) <= 0; sz--);
		ans[sz++] = p[i];
	}
	ans.resize(sz);
}

template <class T>
bool point_in_convex_polygon(const vector<Point<T> > & p, const Point<T> & q, const bool & inclusive = true) 
{
	const int n = p.size();
	if (n == 1) {
		return inclusive && p[0] == q;
	} else if (n == 2) {
		return inclusive && q.on_segment(p[0], p[1]);
	} else if (!q.in_angle(p[0], p[1], p[n - 1])) {
		return false;
	} else if (q.on_line(p[0], p[1]) || q.on_line(p[0], p[n - 1])) {
		return inclusive && (q.on_segment(p[0], p[1]) || q.on_segment(p[0], p[n - 1]));
	} else {
		int low = 1, high = n - 1;
		for (; low < high - 1; ) {
			int mid = low + (high - low) / 2;
			(sgn(q.cross(p[0], p[mid])) < 0 ? high : low) = mid;
		}
		if (q.on_segment(p[low], p[high])) {
			return inclusive;
		} else {
			return q.in_triangle(p[0], p[low], p[high]);
		}
	}
}

template <class T, class U>
inline T & minimize(T & a, const U & b) {
	if (b < a) a = b;
	return a;
}

template <class T>
Point<T> line_line_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2) {
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	return q1 * (-pv2 / (pv1 - pv2)) + q2 * (pv1 / (pv1 - pv2));
}

template <class T>
struct Line {
	Point<T> u, v;

	Line() {

	}

	Line(const Point<T> & u, const Point<T> & v) : u(u), v(v) {

	}

	Line(const T & px, const T & py, const T & qx, const T & qy) : u(px, py), v(qx, qy) {

	}

	T operator * (const Line & rhs) const {
		return (v - u) * (rhs.v - rhs.u);
	}

	T operator & (const Line & rhs) const {
		return (v - u) & (rhs.v - rhs.u);
	}

	bool operator < (const Line & rhs) const {
		int vs = sgn((v - u) * (rhs.v - rhs.u)), ss = sgn((v - u) & (rhs.v - rhs.u));
		if (vs == 0 && ss > 0) return on_left(rhs.u, false);
		else return v - u < rhs.v - rhs.u;
	}

	template <class U>
	bool on_left(const Point<U> & p, const bool & inclusive = true) const {
		return p.cross(u, v) > 0;
	}

	template <class U>
	bool on_right(const Point<U> & p, const bool & inclusive = true) const {
		return p.cross(u, v) < 0;
	}
};

typedef vector<Point<ld>> Polygon;
long double signed_area(Polygon p)
{
	long double area=0;
	for(int i=0;i<p.size();i++)
	{
		int j=i+1;
		j%=p.size();
		area+=p[i].x*p[j].y-p[j].x*p[i].y;
	}
	return area/2.0;
}
long double area(const Polygon &p)
{
	return fabsl(signed_area(p));
}

template <class T>
Point<T> line_line_intersection(const Line<T> & lhs, const Line<T> & rhs) {
	return line_line_intersection(lhs.u, lhs.v, rhs.u, rhs.v);
}

/*
Useful points:
	Brahmagupta formula: area of quadrilateral with sides s1,s2,s3,s4 is given by: 
	s=(s1+s2+s3+s4)/2.0;
	Area=sqrt((s-s1)*(s-s2)*(s-s3)*(s-s4));
*/
