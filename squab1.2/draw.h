/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/




#ifndef DRAW_H
#define DRAW_H

//create a pdf figure of the tiling
//c is 'b' for blue or 'r' for red
extern void DrawMin(struct tiling G, char *pdfName, char c);

//create a pdf figure of the tiling with indices
//pdfName is the name of the output pdf file
//c = 'b' for blue or 'r' for red
extern void Draw(struct tiling G, char *pdfName, char c);

//create a pdf figure of the tiling with indices
//c is 'b' for blue or 'r' for red
//color in red a subset of edges
//the second parameter is the indicator vector of this subset of egdes
extern void HighlightEdges(struct tiling, int *G, char c);

//Write the latex file and plot the performance curves
//the number of elements of the code family is familySize
//errorType = 1 for X and Z error, 2 for Z error, 3 for X error
extern void PlotPerformance(struct storePerformance *perf, int familySize, int errorType);

//generate a pdf with
//(i) a figure of the tiling and its dual
//(ii) the code parameters and overhead
//(iii) the weights of the measurements
//(iv) the performance plotted for X and Z errors, X-errors and Z-errors
extern void Report(struct tiling G, struct tiling H, struct storePerformance *perf, char* timestamp);

//
extern void ComparisonReport(struct storePerformance *perf, int familySize);

#endif	/* DRAW_H */
