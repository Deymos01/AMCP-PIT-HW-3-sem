function res = fence(r,c)
# формирует по заданому количеству строк и столбцов логическую матрицу с чередующимися нулевыми и единичными столбцами.
    if nargin == 1
        c = r;
    endif
    res = zeros(r, c);
    odd_columns = mod(1:c, 2) == 1;
    res(:, odd_columns) = 1;
    res = logical(res);
end
