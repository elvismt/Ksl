/*
 * Copyright (C) 2016  Elvis M.Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <Gde/LinReg.h>
using namespace Gde;

#include <iostream>
using namespace std;

int main()
{
    array1d vx = { 1970, 1980, 1990, 2000 };
    array1d vy = {   12,   11,   14,   13 };

    auto regsol = linreg(vx, vy);

    cout << vx << endl;
    cout << vy << endl;
    cout << "if y = a*x + b then a~" << regsol[1] << " and b~" << regsol[0] << endl;

    return 0;
}
