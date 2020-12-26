InvoiceItemSchema.statics.findById = async (_id) => {
    console.log(_id)
  const invoiceItem = await InvoiceItem.findOne({
    _id
  })

  if (!invoiceItem) {
    throw new Error('Unable to find invoice item')
  }

 // console.log(user)
  return invoiceItem
}


InvoiceItemSchema.statics.deleteinvoice = async (_id) => {
    try{
      //console.log("inside function",companyid,typeof data)
      const res = await InvoiceItem.findByIdAndDelete(_id)
    
      if(!res){
        throw newError('No invoice item with given id')
      }
  
      return true
    }
    catch(e)
    {
      console.log(e)
    }
  }


InvoiceItemSchema.statics.findByInvoiceId = async (invoiceId)=> {

    const invoiceItems = await InvoiceItem.find({invoiceId})

    if(!invoiceItems)
    {
        throw new Error('No invoice items found')
    }

    return invoiceItems
}

InvoiceItemSchema.statics.updateinvoiceitem = async (invoiceId, data) => {
    try{
      //console.log("inside function",partyid,typeof data)
      const res = await InvoiceItem.updateOne({invoiceId: invoiceId}, data)
    
      if(!res){
        throw newError('No invoice item with given id')
      }
  
      return true
    }
    catch(e)
    {
      console.log(e)
    }
  }
const InvoiceItem = mongoose.model('InvoiceItem', InvoiceItemSchema);
module.exports = InvoiceItem;
