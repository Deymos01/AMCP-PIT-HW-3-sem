link1 = struct("m", 1, "l", 1);
link2 = struct("m", 1, "l", 1);
theta = [pi, pi];
ts = [0, 100];

[t, x] = pendux2(link1, link2, theta, ts);

figure;
hold on;
axis equal;
xlim([-2, 2]);
ylim([-2, 2]);

h1 = plot([0 x(1,1)], [0 x(2,1)], 'r', 'LineWidth', 3);  % Первое звено
h2 = plot([x(1,1) x(3,1)], [x(2,1) x(4,1)], 'b', 'LineWidth', 3);  % Второе звено
h3 = plot(x(1,1), x(2,1), 'ko', 'MarkerSize', 15, 'MarkerFaceColor', 'r');  % Узел первого звена
h4 = plot(x(3,1), x(4,1), 'ko', 'MarkerSize', 15, 'MarkerFaceColor', 'b');  % Узел второго звена

trajectory1 = plot(x(1,1), x(2,1), 'r--');  % Траектория первого звена
trajectory2 = plot(x(3,1), x(4,1), 'b--');  % Траектория второго звена

% Массивы для хранения траекторий
trajectory1_x = x(1, 1);
trajectory1_y = x(2, 1);
trajectory2_x = x(3, 1);
trajectory2_y = x(4, 1);

% Анимация движения
for k = 1:length(t)
    set(h1, 'XData', [0 x(1,k)], 'YData', [0 x(2,k)]);
    set(h3, 'XData', x(1,k), 'YData', x(2,k));

    set(h2, 'XData', [x(1,k) x(3,k)], 'YData', [x(2,k) x(4,k)]);
    set(h4, 'XData', x(3,k), 'YData', x(4,k));

    set(trajectory1, 'XData', trajectory1_x, 'YData', trajectory1_y);
    set(trajectory2, 'XData', trajectory2_x, 'YData', trajectory2_y);

    % Обновление траекторий
    trajectory1_x = [trajectory1_x, x(1,k)];
    trajectory1_y = [trajectory1_y, x(2,k)];
    trajectory2_x = [trajectory2_x, x(3,k)];
    trajectory2_y = [trajectory2_y, x(4,k)];

    % Обновление графики
    drawnow;

    % Пауза для видимой анимации
    pause(0.01);
end

hold off;

