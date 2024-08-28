#include <iostream>
#include <math.h>

using f_t = long long;

class Vec {
private:
	f_t x, y, z;

	Vec(f_t x, f_t y, f_t z) : x(x), y(y), z(z) {}
public:
	Vec() : x(0), y(0), z(0) {}

	friend std::istream& operator >> (std::istream& in, Vec& vec)
	{
		f_t x, y, z;
		in >> x >> y >> z;
		vec.x = x;
		vec.y = y;
		vec.z = z;
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, const Vec& vec)
	{
		return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
	}

	f_t len() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() {
		auto l = len();
		x /= l;
		y /= l;
		z /= l;
	}

	static Vec cross(const Vec& v1, const Vec& v2) {
		auto x = v1.y * v2.z - v1.z * v2.y;
		auto y = v1.z * v2.x - v1.x * v2.z;
		auto z = v1.x * v2.y - v1.y * v2.x;
		return Vec(x, y, z);
	}

	static f_t dot(const Vec& v1, const Vec& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static f_t distance(const Vec& v1, const Vec& v2) {
		return (v1 - v2).len();
	}

	Vec operator+(const Vec& other) const {
		return Vec(x + other.x, y + other.y, z + other.z);
	}

	Vec operator-(const Vec& other) const {
		return Vec(x - other.x, y - other.y, z - other.z);
	}

	Vec operator-() const {
		return Vec(-x, -y, -z);
	}

	Vec operator*(const f_t& a) const {
		return Vec(x * a, y * a, z * a);
	}
};

Vec find_closest_point(Vec center, f_t radius, Vec normal, Vec point) {
	normal.normalize();
	Vec r = point - center;
	r = r - normal * Vec::dot(r, normal);
	if (r.len() < radius) {
		return center + r;
	}
	else {
		r.normalize();
		return center + r * radius;
	}
}

int main() {
	Vec center, normal, point;
	f_t radius;
	std::cout << "¬ведите координаты центра окружности/n";
	std::cin >> center;
	std::cout << "¬ведите радиус окружности/n";
	std::cin >> radius;
	std::cout << "¬ведите A, B и C плоскости, проход€щей через центр окружности/n";
	std::cin >> normal;
	std::cout << "¬ведите координаты точки/n";
	std::cin >> point;
	auto v = find_closest_point(center, radius, normal, point);
	std::cout << v;
	return 0;
}