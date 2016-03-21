#include <Ksl/MultiLinearRegr_p.h>

namespace Ksl {

MultiLinearRegr::MultiLinearRegr()
    : Ksl::Object(new MultiLinearRegrPrivate(this))
{
    KSL_PUBLIC(MultiLinearRegr);
    m->workspace = nullptr;
    m->X = nullptr;
    m->cov = nullptr;
}


void MultiLinearRegr::fitCsv(const Csv &csv) {
    // KSL_PUBLIC(MultiLinearRegr);

}


MultiLinearRegrPrivate::~MultiLinearRegrPrivate() {
    if (workspace)
        gsl_multifit_linear_free(workspace);
    if (X)
        gsl_matrix_free(X);
    if (cov)
        gsl_matrix_free(cov);
}

} // namespace Ksl
