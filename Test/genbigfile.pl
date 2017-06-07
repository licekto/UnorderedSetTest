use warnings;
use strict;
use feature qw(say);
use Bytes::Random::Secure qw(random_bytes_base64);
use List::Util 'shuffle';

my $num_bytes = 50;
my $inputs_count;

if ($#ARGV == 0)
{
	$inputs_count = $ARGV[0];
}
else
{
	say "usage: genbigfile.pl <number_of_items>";
	exit;
}

open my $fh, '>', "sample_input.txt";
for my $i (1..$inputs_count)
{
	my $random_bytes_b64 = random_bytes_base64($num_bytes);
	print $fh $random_bytes_b64;
}
close $fh;
