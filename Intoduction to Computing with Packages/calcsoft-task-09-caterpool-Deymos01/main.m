% Тестовые данные для функции caterpillar
##t = linspace(0, 4*pi, 200);
##a = 0.1;
##x = (a * t) .* cos(t);
##y = (a * t) .* sin(t);
%==============================
##x = linspace(1, 10, 100);
##f = @(t) (sin(t));
##y = f(x);
##n = 10;
##caterpillar(x, y, n);

pos = [15, 17];
spee = [1, 1];
bl = [0, 0];
tr = [30, 30];
iterations = 1000;
caterpool(pos, spee, bl, tr, iterations);

