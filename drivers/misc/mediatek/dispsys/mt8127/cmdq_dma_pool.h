#ifndef __CMDQ_DMA_POOL_H__
#define __CMDQ_DMA_POOL_H__
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/dmapool.h>
int cmdq_dma_pool_initialize(struct device *pDev);
int cmdq_dma_pool_deinitialize(void);
int cmdq_alloc_dma_pool(size_t size, dma_addr_t * dma_handle);
int cmdq_free_dma_pool(void * pVA);
#endif