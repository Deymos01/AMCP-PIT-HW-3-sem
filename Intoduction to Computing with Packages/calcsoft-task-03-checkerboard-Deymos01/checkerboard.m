function res = checkerboard(r,c)
# формирует по заданному количеству строк и столбцов логическую матрицу - аналог шахматной доски
    if nargin == 1
        c = r;
    endif
    res = zeros(r, c);
    res(mod(1:r, 2) == 1, mod(1:c, 2) == 1) = 1; % нечетные строки
    res(mod(1:r, 2) == 0, mod(1:c, 2) == 0) = 1; % четные строки
    res = logical(res);
end
