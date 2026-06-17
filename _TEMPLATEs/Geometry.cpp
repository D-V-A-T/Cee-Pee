#define GT template<class T>
#define dbl long double
const dbl PI = acosl(-1), epsilon = 1e-9;
GT struct Ln;
GT struct Pt;
GT T cross(const Pt<T> &a, const Pt<T> &b){return a.x * b.y - b.x * a.y;}
GT T angle(const Pt<T> &a, const Pt<T> &b){return acosl((a*b) / (a.len() * b.len()));}
GT T triA(const Pt<T> &a, const Pt<T> &b, const Pt<T> &c){return abs(cross(b-a, c-a))*.5l;}
GT Pt<T> intersex(const Ln<T> &a, const Ln<T> &b){
    T nux = a.b*b.c - a.c*b.b, nuy = b.a*a.c - b.c*a.a;
    T de = a.a*b.b - a.b*b.a;
    return abs(de) <= epsilon ? Pt<T>(NAN, NAN) : Pt<T>(nux/de, nuy/de);
}
GT bool on_segment(const Pt<T> &p, const Pt<T> &a, const Pt<T> &b){
    if(abs(cross(a - p, b - p)) > epsilon) return false;
    return ((a-p)*(b-p))<=epsilon;
}
GT struct Pt{
    T x, y;

    Pt(T x=0, T y=0){
        this -> x = x;
        this -> y = y;
    }

    T sq(T x)const{return x*x;}
    long double len()const{return sqrtl(x*x + y*y);}
    long double dist_to(const Pt &o)const{return sqrtl(1.0l*sq(x - o.x) + 1.0l*sq(y - o.y));}
    long double dist_to(const Ln<T> &o)const{return triA(*this, o.s, o.r)*2.0l / o.s.dist_to(o.r);}
    Pt operator + (const Pt &o) const {return Pt(x+o.x, y+o.y);}
    Pt operator - (const Pt &o) const {return Pt(x-o.x, y-o.y);}
    Pt operator * (T k) const {return Pt(x*k, y*k);}
    T operator * (const Pt &o) const {return x*o.x + y*o.y;}
    Pt height(const Ln<T> &o) const{
        Ln<T> tmp = o;
        tmp.a = -o.b;
        tmp.b = o.a;
        tmp.c = - (tmp.a * x + tmp.b * y);
        return intersex(tmp, o);
    }

};
GT struct Ln{
    T a, b, c;
    Pt<T> s, r;

    Ln(T a=0, T b=1, T c=0){
        this -> a = a;
        this -> b = b;
        this -> c = c;
        getpoints();
    }

    void getpoints(){
        if(b != 0){
            s = Pt<T>(1, (-c-a)/b);
            r = Pt<T>(0, -c/b);
        }else{
            s = Pt<T>((-c-b)/a, 1);
            r = Pt<T>(-c/a, 0);
        }
    }

    Ln<T> perp(){return Ln<T>(-b, a, c);}

    Ln(const Pt<T> &q, const Pt<T> &t){
        a = q.y - t.y;
        b = t.x - q.x;
        c = -(a*q.x + b*q.y);
        // cout << "? " << a << ' ' << b << ' ' << c << el;
        s = q;
        r = t;
    }
};