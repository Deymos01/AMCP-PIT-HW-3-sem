function caterpillar(x,y,n)
% Отрисовывает "гусеницу" в движении по кривой
% x, y - координаты точек кривой
% n - количество частей "гусеницы"
    if n > length(x)
        return
    endif

    figure;
    hold on;
    plot(x, y);
    axis equal;

    snake = []
    for i = 1:n
        snake(i) = plot(x(i), y(i), 'go', 'MarkerSize', 5, 'MarkerFaceColor', 'g');
    endfor

    for i = 1:(length(x) - n)
        for j = 1:n
            set(snake(j), 'XData', x(i + j), 'YData', y(i + j));
        endfor

        drawnow;
        pause(0.01);
    endfor

    hold off;
endfunction
