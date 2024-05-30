function caterpool(pos,spee,bl,tr,n)
  % pos - начальное положение [x, y]
  % spee - начальная скорость [vx, vy]
  % bl - координаты левого нижнего угла [x, y]
  % tr - координаты правого верхнего угла [x, y]
  % n - количество итераций

   x = pos(1);
   y = pos(2);
   vx = spee(1);
   vy = spee(2);

   figure;
   hold on;
   axis equal;

   rectangle('Position', [bl(1), bl(2), tr(1) - bl(1), tr(2) - bl(2)], 'EdgeColor', 'r');

##    snake = plot(x, y, 'go', 'MarkerSize', 5, 'MarkerFaceColor', 'g');
##
##    for i = 1:n
##        x = x + vx;
##        y = y + vy;
##
##        if x <= bl(1) || x >= tr(1)
##            vx = -vx;
##        endif
##        if y <= bl(2) || y >= tr(2)
##            vy = -vy;
##        endif
##
##        set(snake, 'XData', x, 'YData', y);
##
##        drawnow;
##        pause(0.01);
##    endfor

    snake = cell(1, 10);
    for i = 1:10
        snake{i} = [plot(x + i * (-vx), y + i * (-vy), 'go', 'MarkerSize', 5, 'MarkerFaceColor', 'g'); x + i * (-vx); y + i * (-vy); vx; vy];
    endfor

    for i = 1:n

        for j = 1:10
            xTmp = snake{j}(2) + snake{j}(4);
            yTmp = snake{j}(3) + snake{j}(5);
            snake{j}(2) = xTmp;
            snake{j}(3) = yTmp;
            if xTmp <= bl(1) || xTmp >= tr(1)
                snake{j}(4) = -snake{j}(4);
            endif
            if yTmp <= bl(2) || yTmp >= tr(2)
                snake{j}(5) = -snake{j}(5);
            endif
            set(snake{j}(1), 'XData', xTmp, 'YData', yTmp);

##            snakeSegment = snake{j};
##            snakeSegmentHandle = snakeSegment(1);
##            xTmp = snakeSegment{2} + snakeSegment{4};
##            yTmp = snakeSegment{3} + snakeSegment{5};
##            snake{j}{2} = xTmp;
##            snake{j}{3} = yTmp;
##            if xTmp <= bl(1) || xTmp >= tr(1)
##                snake{j}{4} = -snake{j}{4};
##            endif
##            if yTmp <= bl(2) || yTmp >= tr(2)
##                snake{j}{5} = -snake{j}{5};
##            endif
##            set(snakeSegment{1}, 'XData', xTmp, 'YData', yTmp);
        endfor

        drawnow;
        pause(0.1);
    endfor

   hold off;
endfunction
