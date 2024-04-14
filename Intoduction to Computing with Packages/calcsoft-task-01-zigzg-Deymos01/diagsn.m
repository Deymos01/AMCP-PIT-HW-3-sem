function  res = diagsn(r, c)
% заполняет прямоугольную матрицу натуральными числами в виде "змейки" по диагонали
  rows = r;
  cols = r;
  if nargin == 2
      cols = c;
  endif

  A = zeros(rows, cols);
  currRow = 1;
  currCol = 1;
  counter = 1;
  isUp = 0;
  while currRow <= rows && currCol <= cols
      A(currRow, currCol) = counter;
      ++counter;
      if isUp == 0 % Move left-down
          if currRow == rows % at bottom of matrix
              ++currCol;
              isUp = 1;
          elseif currCol == 1  % at left bound of matrix
              if currRow == rows % at bottom of matrix
                  ++currCol;
              else
                  ++currRow;
              endif
              isUp = 1;
          else % at center of matrix
              ++currRow;
              --currCol;
          endif
      else % Move right-up
          if currRow == 1 % at up bound of matrix
              if currCol == cols % at right bound of matrix
                  ++currRow;
              else
                  ++currCol;
              endif
              isUp = 0;
          elseif currCol == cols % at right bound of matrix
              ++currRow;
              isUp = 0;
          else % at center of matrix
              --currRow;
              ++currCol;
          endif
      endif
  endwhile
  retval = uint32(A);
end
  
