const double EPS = 1e-9;

/*
 * Verified by: POJ 1418 (http://poj.org/problem?id=1418)
 */
void circle_intersect(double r1,
		      double x2, double y2, double r2,
		      bool &ok,
		      pair<double, double> &p1,
		      pair<double, double> &p2
		      ) {
  // Intersection of
  // x^2 + y^2 = r1^2 and 2 * x2 * x + 2 * y2 * y = r1^2 - r2^2 + x2^2 + y2^2
  double a = 2 * x2;
  double b = 2 * y2;
  double c = r1 * r1 - r2 * r2 + x2 * x2 + y2 * y2;
  double dist = c / sqrt(a * a + b * b);
  if (dist >= r1 + EPS) {
    ok = false;
    return;
  }
  double tt = sqrt(r1 * r1 - dist * dist);
  double r = sqrt(x2 * x2 + y2 * y2);
  double ux = x2 / r;
  double uy = y2 / r;
  p1.first = ux * dist + uy * tt;
  p1.second = uy * dist - ux * tt;
  p2.first = ux * dist - uy * tt;
  p2.second = uy * dist + ux * tt;
  ok = true;
}

void circle_line_intersect(double r, double x0, double y0,
			   double a, double b, double c,
			   bool &intersect,
			   pair<double, double> &p1,
			   pair<double, double> &p2
			   ) {
  /*
   * (x - x0)^2 + (y - y0)^2 = r^2
   * a * x + b * y = c
   */
  double rab = sqrt(a * a + b * b);
  double dist = (a * x0 + b * y0 - c) / rab;
  if (abs(dist) >= r + EPS) {
    intersect = false;
    return;
  }
  double x1 = x0 - dist * a / rab;
  double y1 = y0 - dist * b / rab;
  double tt = sqrt(r * r - dist * dist);
  intersect = true;
  p1.first = x1 + tt * b / rab;
  p1.second = y1 - tt * a / rab;
  p2.first = x1 - tt * b / rab;
  p2.second = y1 + tt * a / rab;
}

/*
 * Verified by: POJ 1418 (http://poj.org/problem?id=1418)
 */
void line_points(pair<double, double> p1,
		 pair<double, double> p2,
		 double &a, double &b, double &c) {
  a = p2.second - p1.second;
  b = p1.first - p2.first;
  c = a * p1.first + b * p1.second;
}
