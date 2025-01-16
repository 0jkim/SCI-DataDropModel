/*
 * Copyright (c) 2008 University of Washington
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef IPV4_ADDRESS_GENERATOR_H
#define IPV4_ADDRESS_GENERATOR_H

#include "ns3/ipv4-address.h"

namespace ns3
{

/**
 * @ingroup address
 * @ingroup ipv4
 *
 * @brief This generator assigns addresses sequentially from a provided
 * network address; used in topology code.
 *
 * @note BEWARE: this class acts as a Singleton.
 * In other terms, two different instances of Ipv4AddressGenerator will
 * pick IPv4 numbers from the same pool. Changing the network in one of them
 * will also change the network in the other instances.
 *
 */
class Ipv4AddressGenerator
{
  public:
    /**
     * @brief Initialise the base network, mask and address for the generator
     *
     * The first call to NextAddress() or GetAddress() will return the
     * value passed in.
     *
     * @param net The network for the base Ipv4Address
     * @param mask The network mask of the base Ipv4Address
     * @param addr The base address used for initialization
     */
    static void Init(const Ipv4Address net,
                     const Ipv4Mask mask,
                     const Ipv4Address addr = "0.0.0.1");

    /**
     * @brief Get the next network according to the given Ipv4Mask
     *
     * This operation is a pre-increment, meaning that the internal state
     * is changed before returning the new network address.
     *
     * This also resets the address to the base address that was
     * used for initialization.
     *
     * @param mask The Ipv4Mask used to set the next network
     * @returns the IPv4 address of the next network
     */
    static Ipv4Address NextNetwork(const Ipv4Mask mask);

    /**
     * @brief Get the current network of the given Ipv4Mask
     *
     * Does not change the internal state; this just peeks at the current
     * network
     *
     * @param mask The Ipv4Mask for the current network
     * @returns the IPv4 address of the current network
     */
    static Ipv4Address GetNetwork(const Ipv4Mask mask);

    /**
     * @brief Set the address for the given mask
     *
     * @param addr The address to set for the current mask
     * @param mask The Ipv4Mask whose address is to be set
     */
    static void InitAddress(const Ipv4Address addr, const Ipv4Mask mask);

    /**
     * @brief Allocate the next Ipv4Address for the configured network and mask
     *
     * This operation is a post-increment, meaning that the first address
     * allocated will be the one that was initially configured.
     *
     * @param mask The Ipv4Mask for the current network
     * @returns the IPv4 address
     */
    static Ipv4Address NextAddress(const Ipv4Mask mask);

    /**
     * @brief Get the Ipv4Address that will be allocated upon NextAddress ()
     *
     * Does not change the internal state; just is used to peek the next
     * address that will be allocated upon NextAddress ()
     *
     * @param mask The Ipv4Mask for the current network
     * @returns the IPv4 address
     */
    static Ipv4Address GetAddress(const Ipv4Mask mask);

    /**
     * @brief Reset the networks and Ipv4Address to zero
     */
    static void Reset();

    /**
     * @brief Add the Ipv4Address to the list of IPv4 entries
     *
     * Typically, this is used by external address allocators that want
     * to make use of this class's ability to track duplicates.  AddAllocated
     * is always called internally for any address generated by NextAddress ()
     *
     * @param addr The Ipv4Address to be added to the list of Ipv4 entries
     * @returns true on success
     */
    static bool AddAllocated(const Ipv4Address addr);

    /**
     * @brief Check the Ipv4Address allocation in the list of IPv4 entries
     *
     * @param addr The Ipv4Address to be checked in the list of Ipv4 entries
     * @returns true if the network is already allocated
     */
    static bool IsAddressAllocated(const Ipv4Address addr);

    /**
     * @brief Check if a network has already allocated addresses
     *
     * @param addr The Ipv4 network to be checked
     * @param mask The Ipv4 network mask
     * @returns true if the network is already allocated
     */
    static bool IsNetworkAllocated(const Ipv4Address addr, const Ipv4Mask mask);

    /**
     * @brief Used to turn off fatal errors and assertions, for testing
     */
    static void TestMode();
};

} // namespace ns3

#endif /* IPV4_ADDRESS_GENERATOR_H */
