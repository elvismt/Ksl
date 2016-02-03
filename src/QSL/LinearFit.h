#ifndef QSL_LINEARFIT_H
#define QSL_LINEARFIT_H

#include <QSL/Array1D.h>
#include <gsl/gsl_fit.h>

QSL_BEGIN_NAMESPACE

class LinearFit
{
public:

   LinearFit(const Array1D<double> &x,
             const Array1D<double> &y,
             const Array1D<double> &w = Array1D<double>())
      : m_x(x)
      , m_y(y)
      , m_w(w)
   {
      if (x.size() > 0 && w.size() == 0) {
         m_w = array1d(x.size(), 1.0);
      }
   }

   inline void execute() {
      gsl_fit_wlinear(
         m_x.begin(), 1,
         m_w.begin(), 1,
         m_y.begin(), 1,
         m_x.size(),
         &m_par1, &m_par2,
         &m_cov00, &m_cov01, &m_cov11,
         &m_chiSqr
      );
   }

   Array1D<double> solution() const {
      return std::move(Array1D<double>{ m_par1, m_par2 });
   }


private:

   Array1D<double> m_x;
   Array1D<double> m_y;
   Array1D<double> m_w;

   double m_chiSqr;
   double m_par1, m_par2;
   double m_cov00, m_cov01, m_cov11;
};

QSL_END_NAMESPACE

#endif // QSL_LINEARFIT_H
