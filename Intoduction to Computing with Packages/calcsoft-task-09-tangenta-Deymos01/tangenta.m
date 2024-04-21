function tangenta(fd, dmin, dmax, n)
% Функция для построения графика касательной для параметрически заданной плоской кривой
    dmiddle = dmin + (dmax - dmin) / 2;

    t = linspace(dmin, dmax, 2 * n + 1);
    fVals = zeros(2, 2 * n + 1);
    for it = 1:length(t)
        fVals(:,it) = fd(t(it));
    endfor
    xmin = min(fVals(1,:)); xmax = max(fVals(1,:));

    % building a tagent
    df = diffi(fd, dmiddle);
    slope = df(2) / df(1);
    x0 = fd(dmiddle)(1); y0 = fd(dmiddle)(2);
    xTagent = linspace(xmin, xmax, n);
    yTagent = slope * (xTagent - x0) + y0;

    figure;
    hold on;
    plot(fVals(1,:), fVals(2,:), 'LineWidth', 1);
    plot(xTagent, yTagent, 'LineWidth', 1.5);
    plot(x0, y0, 'marker', '.', 'markersize', 10, 'color', 'r');
    axis fill;
    hold off;
endfunction
