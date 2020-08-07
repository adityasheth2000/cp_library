
struct point
{
	ld x,y,z;
	point():x(0),y(0),z(0){}
	point(ld x,ld y,ld z): x(x),y(y),z(z){}
	point operator +(const point &rhs) const{
		return point(x+rhs.x,y+rhs.y,z+rhs.z);
	}
	point operator -(const point &rhs) const{
		return point(x-rhs.x,y-rhs.y,z-rhs.z);
	}
	point operator *(ld k) const{
		return point(x*k,y*k,z*k);
	}
};

/*
Useful points:
1) Rodrigues rotation formula for rotating a vector in 3-D  about an axis of rotation:
If v is a vector in ℝ3 and k is a unit vector describing an axis of rotation about 
which v rotates by an angle θ according to the right hand rule, the Rodrigues formula 
for the rotated vector vrot is:
//vrot= v cos(theta)+ (k x v)sin(theta)+ k(k.v)(1-cos(theta))
*/
point cross(point a,point b)
{
	point tmp;
	tmp.x=a.y*b.z-b.y*a.z;
	tmp.y=b.x*a.z-a.x*b.z;
	tmp.z=a.x*b.y-a.y*b.x;
	return tmp;
}
ld dot(point a,point b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
ld len(point v)
{
	ld len2=v.x*v.x+v.y*v.y+v.z*v.z;
	return sqrtl(len2);
}
ld dis(point a,point b)
{
	return len(a-b);
}
point rot(point v,point axis,ld theta)
{
//vrot= v cos(theta)+ (k x v)sin(theta)+ k(k.v)(1-cos(theta))
	ld l=len(axis);
	axis.x/=l;
	axis.y/=l;
	axis.z/=l;
	point p;
	p=v*cosl(theta)+cross(axis,v)*sinl(theta);
	p=p+axis*(dot(axis,v)*(1-cos(theta)));
	return p;
}