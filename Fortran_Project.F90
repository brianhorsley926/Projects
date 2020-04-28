module PrimeNumbers
implicit none
integer :: n
contains
    logical function IsPrime(n)
        integer :: n, j, counter
        counter = 0
        do j = 2, n/2
            if (MOD(n,j) == 0) then
                counter = counter + 1
                IsPrime = .false.
                exit
            end if
        end do
        if (counter == 0) then
            IsPrime = .true.
        end if
        if (n == 0 .or. n == 1) then
            IsPrime = .false.
        end if
    end function
    integer function NextPrime(n)
        integer :: n, i, j, next, counter
        next = n + 1
        if (n == 0 .or. n == 1) then
            NextPrime = 2
        else if (n > 1) then
            do while(IsPrime(next) == .false.)
                counter = 0
                do j = 2, FLOOR(next**0.5)
                    if (MOD(next,j) == 0) then
                        counter = counter + 1
                        exit
                    end if
                end do
                if (counter == 0) then
                    NextPrime = next
                    exit
                end if
                next = next + 1
            end do
            NextPrime = next
        end if
    end function
    integer function PreviousPrime(n)
        integer :: n, i, j, counter, prev_p
        prev_p = 2
        do i = 0, n-1
            counter = 0
            do j = 2, FLOOR(i**0.5)
                if (i == 0 .or. i == 1) then
                    PreviousPrime = -1
                else if (MOD(i,j) == 0) then
                    counter = counter + 1
                end if
            end do
            if (counter > 0) then
                continue
            else if (n == 2) then
                prev_p = 2
            else if (counter == 0) then
                prev_p = i
            end if
        end do
        PreviousPrime = prev_p
    end function
    subroutine PrimeArray(n, p_arr)
        integer, dimension(:), allocatable :: p_arr
        integer :: n, p, counter, start, ierror
        allocate(p_arr(n), stat=ierror)
        if (ierror /= 0) stop 'error p_arr'
        start = 4
        counter = 1
        do while (counter /= n+1)
            if (IsPrime(start) == .true.) then
                p_arr(counter) = start
                counter = counter + 1
            end if
            start = start + 1
        end do
        return
    end subroutine
    subroutine pq_primes(r, p, q)
        integer :: r, p, q
        p = PreviousPrime(r)
        q = NextPrime(r)
        return
    end subroutine
end module PrimeNumbers

program Fortran_Project
use PrimeNumbers
implicit none
integer :: i, num, p, q, r, counter, upd, ierror
integer, dimension(:), allocatable :: p_arr, dist

print *, 'Goldbach Conjecture'
print *, 'Triple if: r-p == q-r'
print *, ''
num = 10000 
counter = 1
allocate(dist(num), stat=ierror)
if (ierror /= 0) stop 'error dist'
call PrimeArray(num, p_arr)
print *, p_arr
do i = 1, num
    r = p_arr(i)
    call pq_primes(r, p, q)
    if (r-p == q-r) then
        print *, 'Triple ', counter, ': ', r, p, q
        print *, 'Distance (q-r): ', q-r
        print *, ''
        dist(i) = q-r
        counter = counter + 1
    else
        do while(r-p /= q-r)
            r = p_arr(i)
            if (r-p > q-r) then
                q = NextPrime(q)
                if (r-p == q-r) then
                    print *, 'Triple ', counter, ': ', r, p, q
                    print *, 'Distance (q-r): ', q-r
                    print *, ''
                    dist(i) = q-r
                    counter = counter + 1
                    exit
                end if
            else if (q-r > r-p) then
                p = PreviousPrime(p)
                if (r-p == q-r) then
                    print *, 'Triple ', counter, ': ', r, p, q
                    print *, 'Distance (q-r): ', q-r
                    print *, ''
                    dist(i) = q-r
                    counter = counter + 1
                    exit
                end if
            end if
        end do
    end if
end do
print *, SUM(dist)/SIZE(dist)
print *, MAXVAL(dist)
print *, MINVAL(dist)
WRITE(1,1) (dist(i), i = 1, num)
1   FORMAT(I3/)
end program Fortran_Project            
