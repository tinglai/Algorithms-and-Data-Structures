#ifndef GUARD_client_h
#define GUARD_client_h

struct Client_stat{
	long long bought;
	long long sold;
	long long transfer;

	Client_stat():bought(0), sold(0), transfer(0){}
};

#endif
