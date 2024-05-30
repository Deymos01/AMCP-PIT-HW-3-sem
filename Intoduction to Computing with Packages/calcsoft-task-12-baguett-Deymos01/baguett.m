function baguett(l,d,a,n)
% l - длина, d - диаметр, а - угол реза, n - количество кусков
        a = deg2rad(a);
        subplot(1, 2, 1);
        % Создание цилиндра
        [x, y, z] = cylinder(d / 2, 32);
        z = z * l;

        % Вращение цилиндра
        rx = x;
        ry = z;
        rz = -y;

        hold on;
        surf(rx, ry, rz, 'facecolor', 'y');

        % Создание торцов
        theta = 0:pi/16:2*pi;
        x_end = (d/2) * cos(theta);
        y_end = (d/2) * sin(theta);
        z_end = zeros(1, numel(x_end));

        % Поворот торцов
        rx_end = x_end;
        ry_end = cos(pi/2) * y_end + sin(pi/2) * z_end;
        rz_end = -sin(pi/2) * y_end + cos(pi/2) * z_end;
        fill3(rx_end, ry_end, rz_end, 'y'); % Ближний торец
        fill3(rx_end, ry_end + l, rz_end, 'y'); % Дальний торец

        title('original');
        axis equal;
        xlabel('X'); ylabel('Y'); zlabel('Z');

        subplot(1, 2, 2);
        hold on;

        % Формирование части цилиндра и перерасчет длины
        z = z / n;
        ry = cos(a) * y + sin(a) * z;
        rz = -sin(a) * y + cos(a) * z;

        % Расчет наклона торцов
        ry_end = cos(a) * y_end + sin(a) * z_end;
        rz_end = -sin(a) * y_end + cos(a) * z_end;

        k = 1;
        for i = 1:n
            if mod(i, 2) == 1
                surf(rx, ry + l - k * (l / n), rz, 'facecolor', 'y');
                fill3(rx_end, ry_end + l - (l / n) * (k - sin(a)), rz_end + (l / n) * cos(a), 'y');
                fill3(rx_end, ry_end + l - k * (l / n) , rz_end, 'y');
            endif
            k += 1;
        endfor
        title('sliced');
        axis equal;
        xlabel('X'); ylabel('Y'); zlabel('Z');
endfunction
