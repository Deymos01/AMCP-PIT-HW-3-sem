function fracto (p, ll, ur, xx, yy)
    err = 0.01;
    x = linspace(ll(1), ur(1), xx);
    y = linspace(ll(2), ur(2), yy);

    r = roots(p);

    [X, Y] = meshgrid(x, y);
    complexSurface = complex(X, Y);
    func = @(x) polyval(p, x);
    derFunc = @(x) polyval(polyder(p), x);
## calculate values
    values = newtonsMethod(complexSurface, func, derFunc,  100);

##    set colors
    colors = [];
    loading = 0;
    for xIter = 1:size(x, 2)
        tmp = ceil((xIter / size(x,2))*100);
        if mod(tmp, 20) == 0 && loading != tmp
                printf("Loading... %d%%\n", tmp);
                loading = tmp;
        endif
        for yIter = 1:size(y, 2)
            value = values(xIter, yIter);
            if isnan(real(value)) || isnan(imag(value))
                 colors(xIter, yIter) = 0;
                 continue;
             endif
             for rootIter = 1:size(r, 1)
                 if abs(r(rootIter) - value) < err
                     colors(xIter, yIter) = rootIter;
                     break;
                 endif
             endfor
        endfor
    endfor
    image(x, y, colors, 'CDataMapping', 'scaled');
    colorbar;
    axis xy;
    axis equal;
endfunction

function root = newtonsMethod (start_x, func, derivative, iter = 100)
       xn = start_x - (func(start_x) ./ derivative(start_x));
        for k = 1:iter
            xn = xn - (func(xn)./derivative(xn));
        endfor
        root = xn;
endfunction
